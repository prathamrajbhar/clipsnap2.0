#pragma once
#include <QObject>

class AppController : public QObject {
    Q_OBJECT
    Q_PROPERTY(bool monitoringActive READ monitoringActive NOTIFY monitoringActiveChanged)

public:
    explicit AppController(QObject* parent = nullptr);

    bool monitoringActive() const;

    Q_INVOKABLE void openSettings();
    Q_INVOKABLE void requestCapture();
    Q_INVOKABLE void pauseMonitoring();
    Q_INVOKABLE void resumeMonitoring();
    Q_INVOKABLE void toggleMonitoring();
    Q_INVOKABLE void checkActiveClipboard();

signals:
    void monitoringActiveChanged();
    void historyRequested();
    void captureRequested();
    void settingsRequested();
    void clipboardCheckRequested();

private:
    bool m_monitoringActive = true;
};
