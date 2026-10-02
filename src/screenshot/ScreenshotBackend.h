#pragma once
#include <QObject>
#include <QImage>
#include <QRect>

class ScreenshotBackend : public QObject {
    Q_OBJECT
public:
    explicit ScreenshotBackend(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~ScreenshotBackend() = default;

    // Start a screenshot capture. Result arrives via one of the signals below.
    // For portal backends: hides app window first, then calls portal, then shows crop UI.
    Q_INVOKABLE virtual void startCapture() = 0;
    Q_INVOKABLE virtual QString backendName() const = 0;
    Q_INVOKABLE virtual bool supportsNativeRegion() const = 0;

signals:
    void captureComplete(QImage image, QRect capturedRegion);
    void captureCancelled();
    void capturePermissionDenied();
    void captureUnsupported(QString reason);
    void captureError(QString message);
};
