#pragma once

#include <QObject>
#include <QStringList>

class Settings;
class SingleInstance;
class HistoryRepository;

class ClipboardBackend;

class Application : public QObject {
    Q_OBJECT
public:
    explicit Application(QObject* parent = nullptr);
    ~Application();

    void initialize();
    SingleInstance* singleInstance() const { return m_singleInstance; }
    HistoryRepository* history() const { return m_history; }
    ClipboardBackend* clipboardBackend() const { return m_clipboardBackend; }

    void saveImageToHistory(const QImage& image, const QString& origin = QStringLiteral("screenshot"));
    void checkClipboardNow();

signals:
    void captureRequested();
    void historyRequested();
    void pauseRequested();
    void resumeRequested();

public slots:
    void handleCommand(const QStringList& args);

private:
    SingleInstance* m_singleInstance = nullptr;
    HistoryRepository* m_history = nullptr;
    ClipboardBackend* m_clipboardBackend = nullptr;
};
