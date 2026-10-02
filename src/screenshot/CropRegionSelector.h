#pragma once
#include <QObject>
#include <QImage>
#include <QRectF>

class CropRegionSelector : public QObject {
    Q_OBJECT
    Q_PROPERTY(QImage sourceImage READ sourceImage WRITE setSourceImage NOTIFY sourceImageChanged)
    Q_PROPERTY(QRectF selection READ selection WRITE setSelection NOTIFY selectionChanged)
    Q_PROPERTY(int imageWidth READ imageWidth NOTIFY sourceImageChanged)
    Q_PROPERTY(int imageHeight READ imageHeight NOTIFY sourceImageChanged)
public:
    explicit CropRegionSelector(QObject* parent = nullptr);

    QImage sourceImage() const;
    void setSourceImage(const QImage& image);

    QRectF selection() const;
    void setSelection(const QRectF& rect);

    int imageWidth() const;
    int imageHeight() const;

    Q_INVOKABLE void confirmCrop(); // emits cropConfirmed with cropped QImage
    Q_INVOKABLE void cancel();      // emits cropCancelled
    // Coordinate helpers
    Q_INVOKABLE QRectF normalizeRect(qreal x1, qreal y1, qreal x2, qreal y2) const;

signals:
    void cropConfirmed(QImage croppedImage);
    void cropCancelled();
    void sourceImageChanged();
    void selectionChanged();

private:
    QImage m_sourceImage;
    QRectF m_selection; // normalized 0..1 rect
};
