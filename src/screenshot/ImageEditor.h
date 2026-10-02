#pragma once
#include <QObject>
#include <QImage>
#include <QRectF>
#include <QQuickImageProvider>

class ImageEditor : public QQuickImageProvider {
    Q_OBJECT
public:
    explicit ImageEditor(QObject* parent = nullptr);
    
    QImage requestImage(const QString &id, QSize *size, const QSize &requestedSize) override;

    Q_INVOKABLE void setImage(const QImage& image);
    Q_INVOKABLE void crop(const QRectF& normalizedRect);
    Q_INVOKABLE void cropAndCopy(double nx, double ny, double nw, double nh);
    Q_INVOKABLE void cropAndSave(double nx, double ny, double nw, double nh);
    Q_INVOKABLE void copyFullScreen();
    Q_INVOKABLE void saveFullScreen();

    Q_INVOKABLE void addArrow(double sx, double sy, double ex, double ey, const QString& colorHex);
    Q_INVOKABLE void addRectangle(double nx, double ny, double nw, double nh, const QString& colorHex);
    Q_INVOKABLE void addText(double nx, double ny, const QString& text, const QString& colorHex);
    Q_INVOKABLE void addRedaction(double nx, double ny, double nw, double nh);
    
    Q_INVOKABLE void undo();
    Q_INVOKABLE void redo();
    
    Q_INVOKABLE void commit(); // emits editFinished
    Q_INVOKABLE void cancel(); // clears
    
    Q_INVOKABLE bool canUndo() const { return !m_undoStack.isEmpty(); }
    Q_INVOKABLE bool canRedo() const { return !m_redoStack.isEmpty(); }

signals:
    void imageChanged();
    void editFinished(const QImage& finalImage);
    void stateChanged(); // undo/redo availability changed

private:
    void pushState();

    QList<QImage> m_undoStack;
    QList<QImage> m_redoStack;
    QImage m_originalImage;
    QImage m_currentImage;
};
