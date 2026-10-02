#include "CropRegionSelector.h"

CropRegionSelector::CropRegionSelector(QObject* parent)
    : QObject(parent)
{
}

QImage CropRegionSelector::sourceImage() const
{
    return m_sourceImage;
}

void CropRegionSelector::setSourceImage(const QImage& image)
{
    m_sourceImage = image;
    emit sourceImageChanged();
}

QRectF CropRegionSelector::selection() const
{
    return m_selection;
}

void CropRegionSelector::setSelection(const QRectF& rect)
{
    m_selection = rect;
    emit selectionChanged();
}

int CropRegionSelector::imageWidth() const
{
    return m_sourceImage.width();
}

int CropRegionSelector::imageHeight() const
{
    return m_sourceImage.height();
}

void CropRegionSelector::confirmCrop()
{
    if (m_sourceImage.isNull() || !m_selection.isValid()) {
        emit cropCancelled();
        return;
    }

    int x = static_cast<int>(m_selection.x() * m_sourceImage.width());
    int y = static_cast<int>(m_selection.y() * m_sourceImage.height());
    int w = static_cast<int>(m_selection.width() * m_sourceImage.width());
    int h = static_cast<int>(m_selection.height() * m_sourceImage.height());

    QRect cropRect(x, y, w, h);
    cropRect = cropRect.intersected(m_sourceImage.rect());

    QImage cropped = m_sourceImage.copy(cropRect);
    emit cropConfirmed(cropped);
}

void CropRegionSelector::cancel()
{
    emit cropCancelled();
}

QRectF CropRegionSelector::normalizeRect(qreal x1, qreal y1, qreal x2, qreal y2) const
{
    if (m_sourceImage.isNull()) return QRectF();

    qreal nx = std::min(x1, x2) / m_sourceImage.width();
    qreal ny = std::min(y1, y2) / m_sourceImage.height();
    qreal nw = std::abs(x2 - x1) / m_sourceImage.width();
    qreal nh = std::abs(y2 - y1) / m_sourceImage.height();

    return QRectF(nx, ny, nw, nh);
}
