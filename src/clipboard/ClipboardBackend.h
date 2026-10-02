#pragma once
#include <QObject>
#include <QImage>

class ClipboardBackend : public QObject {
    Q_OBJECT
public:
    explicit ClipboardBackend(QObject* parent = nullptr) : QObject(parent) {}
    virtual ~ClipboardBackend() = default;

    virtual void startMonitoring() = 0;
    virtual void stopMonitoring() = 0;
    virtual bool isMonitoring() const = 0;
    virtual QString backendName() const = 0;
    virtual void checkClipboard() {}

signals:
    void clipboardTextChanged(const QString& text);
    void clipboardImageChanged(const QImage& image);
};
