#include "ImageEditor.h"
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QFont>
#include <QPolygonF>
#include <QtMath>
#include <QGuiApplication>
#include <QClipboard>
#include <QStandardPaths>
#include <QDir>
#include <QDateTime>
#include <algorithm>

ImageEditor::ImageEditor(QObject* parent)
    : QQuickImageProvider(QQuickImageProvider::Image)
{
    Q_UNUSED(parent);
}

QImage ImageEditor::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    const QImage& src = (id.startsWith("original") || m_currentImage.isNull()) ? m_originalImage : m_currentImage;
    if (size) *size = src.size();
    
    if (!requestedSize.isEmpty()) {
        return src.scaled(requestedSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    }
    return src;
}

void ImageEditor::setImage(const QImage& image)
{
    m_undoStack.clear();
    m_redoStack.clear();
    m_originalImage = image;
    m_currentImage = image;
    emit imageChanged();
    emit stateChanged();
}

void ImageEditor::pushState()
{
    m_undoStack.append(m_currentImage);
    m_redoStack.clear();
    emit stateChanged();
}

void ImageEditor::undo()
{
    if (m_undoStack.isEmpty()) return;
    m_redoStack.append(m_currentImage);
    m_currentImage = m_undoStack.takeLast();
    emit imageChanged();
    emit stateChanged();
}

void ImageEditor::redo()
{
    if (m_redoStack.isEmpty()) return;
    m_undoStack.append(m_currentImage);
    m_currentImage = m_redoStack.takeLast();
    emit imageChanged();
    emit stateChanged();
}

void ImageEditor::crop(const QRectF& normalizedRect)
{
    if (m_currentImage.isNull()) return;
    pushState();
    
    int x = qRound(normalizedRect.x() * m_currentImage.width());
    int y = qRound(normalizedRect.y() * m_currentImage.height());
    int w = qRound(normalizedRect.width() * m_currentImage.width());
    int h = qRound(normalizedRect.height() * m_currentImage.height());
    
    QRect cropRect(x, y, w, h);
    m_currentImage = m_currentImage.copy(cropRect.intersected(m_currentImage.rect()));
    emit imageChanged();
}

void ImageEditor::cropAndCopy(double nx, double ny, double nw, double nh)
{
    const QImage& src = m_originalImage.isNull() ? m_currentImage : m_originalImage;
    if (src.isNull()) return;

    int x = std::clamp(qRound(nx * src.width()), 0, src.width() - 1);
    int y = std::clamp(qRound(ny * src.height()), 0, src.height() - 1);
    int w = std::clamp(qRound(nw * src.width()), 1, src.width() - x);
    int h = std::clamp(qRound(nh * src.height()), 1, src.height() - y);

    QImage cropped = src.copy(x, y, w, h);
    QGuiApplication::clipboard()->setImage(cropped);
    emit editFinished(cropped);
}

void ImageEditor::cropAndSave(double nx, double ny, double nw, double nh)
{
    const QImage& src = m_originalImage.isNull() ? m_currentImage : m_originalImage;
    if (src.isNull()) return;

    int x = std::clamp(qRound(nx * src.width()), 0, src.width() - 1);
    int y = std::clamp(qRound(ny * src.height()), 0, src.height() - 1);
    int w = std::clamp(qRound(nw * src.width()), 1, src.width() - x);
    int h = std::clamp(qRound(nh * src.height()), 1, src.height() - y);

    QImage cropped = src.copy(x, y, w, h);
    QGuiApplication::clipboard()->setImage(cropped);

    QString screenshotsDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Screenshots";
    QDir().mkpath(screenshotsDir);
    QString filename = "Screenshot_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss") + ".png";
    QString filePath = screenshotsDir + "/" + filename;
    cropped.save(filePath, "PNG");

    emit editFinished(cropped);
}

void ImageEditor::copyFullScreen()
{
    const QImage& src = m_originalImage.isNull() ? m_currentImage : m_originalImage;
    if (src.isNull()) return;
    QGuiApplication::clipboard()->setImage(src);
    emit editFinished(src);
}

void ImageEditor::saveFullScreen()
{
    const QImage& src = m_originalImage.isNull() ? m_currentImage : m_originalImage;
    if (src.isNull()) return;
    QGuiApplication::clipboard()->setImage(src);

    QString screenshotsDir = QStandardPaths::writableLocation(QStandardPaths::PicturesLocation) + "/Screenshots";
    QDir().mkpath(screenshotsDir);
    QString filename = "Screenshot_" + QDateTime::currentDateTime().toString("yyyy-MM-dd_HH-mm-ss") + ".png";
    QString filePath = screenshotsDir + "/" + filename;
    src.save(filePath, "PNG");

    emit editFinished(src);
}

void ImageEditor::addArrow(double nx1, double ny1, double nx2, double ny2, const QString& colorHex)
{
    if (m_currentImage.isNull()) return;
    pushState();
    
    QPainter p(&m_currentImage);
    p.setRenderHint(QPainter::Antialiasing);
    QColor c(colorHex);
    p.setPen(QPen(c, 4, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    p.setBrush(c);
    
    double w = m_currentImage.width();
    double h = m_currentImage.height();
    QPointF start(nx1 * w, ny1 * h);
    QPointF end(nx2 * w, ny2 * h);
    
    p.drawLine(start, end);
    
    // Draw arrowhead
    double angle = std::atan2(end.y() - start.y(), end.x() - start.x());
    double arrowSize = 15;
    QPointF p1 = end - QPointF(sin(angle + M_PI / 3) * arrowSize, cos(angle + M_PI / 3) * arrowSize);
    QPointF p2 = end - QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize, cos(angle + M_PI - M_PI / 3) * arrowSize);
    
    QPolygonF arrowHead;
    arrowHead << end << p1 << p2;
    p.drawPolygon(arrowHead);
    
    emit imageChanged();
}

void ImageEditor::addRectangle(double nx, double ny, double nw, double nh, const QString& colorHex)
{
    if (m_currentImage.isNull()) return;
    pushState();
    
    QPainter p(&m_currentImage);
    p.setRenderHint(QPainter::Antialiasing);
    p.setPen(QPen(QColor(colorHex), 4));
    
    double w = m_currentImage.width();
    double h = m_currentImage.height();
    p.drawRect(QRectF(nx * w, ny * h, nw * w, nh * h));
    
    emit imageChanged();
}

void ImageEditor::addText(double nx, double ny, const QString& text, const QString& colorHex)
{
    if (m_currentImage.isNull() || text.isEmpty()) return;
    pushState();
    
    QPainter p(&m_currentImage);
    p.setRenderHint(QPainter::TextAntialiasing);
    p.setPen(QColor(colorHex));
    QFont font = p.font();
    font.setPixelSize(24);
    p.setFont(font);
    
    double w = m_currentImage.width();
    double h = m_currentImage.height();
    p.drawText(QPointF(nx * w, ny * h), text);
    
    emit imageChanged();
}

void ImageEditor::addRedaction(double nx, double ny, double nw, double nh)
{
    if (m_currentImage.isNull()) return;
    pushState();
    
    QPainter p(&m_currentImage);
    p.setRenderHint(QPainter::Antialiasing, false);
    p.setPen(Qt::NoPen);
    p.setBrush(Qt::black);
    
    double w = m_currentImage.width();
    double h = m_currentImage.height();
    p.drawRect(QRectF(nx * w, ny * h, nw * w, nh * h));
    
    emit imageChanged();
}

void ImageEditor::commit()
{
    emit editFinished(m_currentImage);
}

void ImageEditor::cancel()
{
    m_undoStack.clear();
    m_redoStack.clear();
    m_currentImage = QImage();
    m_originalImage = QImage();
}
