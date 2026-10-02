#pragma once

#include <QObject>
#include <QString>
#include <QSettings>

class Settings : public QObject {
    Q_OBJECT
    Q_PROPERTY(int maxHistoryEntries READ maxHistoryEntries WRITE setMaxHistoryEntries NOTIFY maxHistoryEntriesChanged)
    Q_PROPERTY(int retentionDays READ retentionDays WRITE setRetentionDays NOTIFY retentionDaysChanged)
    Q_PROPERTY(int maxStorageMb READ maxStorageMb WRITE setMaxStorageMb NOTIFY maxStorageMbChanged)
    Q_PROPERTY(int maxPayloadSizeKb READ maxPayloadSizeKb WRITE setMaxPayloadSizeKb NOTIFY maxPayloadSizeKbChanged)
    Q_PROPERTY(int maxImagePixels READ maxImagePixels WRITE setMaxImagePixels NOTIFY maxImagePixelsChanged)
    Q_PROPERTY(QString shortcutCapture READ shortcutCapture WRITE setShortcutCapture NOTIFY shortcutCaptureChanged)
    Q_PROPERTY(QString shortcutHistory READ shortcutHistory WRITE setShortcutHistory NOTIFY shortcutHistoryChanged)
    Q_PROPERTY(bool monitoringEnabled READ monitoringEnabled WRITE setMonitoringEnabled NOTIFY monitoringEnabledChanged)
    Q_PROPERTY(bool autostartEnabled READ autostartEnabled WRITE setAutostartEnabled NOTIFY autostartEnabledChanged)

public:
    static Settings* instance();

    QString configDir() const;
    QString dataDir() const;
    QString stateDir() const;

    int maxHistoryEntries() const;
    void setMaxHistoryEntries(int value);

    int retentionDays() const;
    void setRetentionDays(int value);

    int maxStorageMb() const;
    void setMaxStorageMb(int value);

    int maxPayloadSizeKb() const;
    void setMaxPayloadSizeKb(int value);

    int maxImagePixels() const;
    void setMaxImagePixels(int value);

    QString shortcutCapture() const;
    void setShortcutCapture(const QString& value);

    QString shortcutHistory() const;
    void setShortcutHistory(const QString& value);

    bool monitoringEnabled() const;
    void setMonitoringEnabled(bool value);

    bool autostartEnabled() const;
    void setAutostartEnabled(bool value);

signals:
    void maxHistoryEntriesChanged();
    void retentionDaysChanged();
    void maxStorageMbChanged();
    void maxPayloadSizeKbChanged();
    void maxImagePixelsChanged();
    void shortcutCaptureChanged();
    void shortcutHistoryChanged();
    void monitoringEnabledChanged();
    void autostartEnabledChanged();

private:
    Settings(QObject* parent = nullptr);
    ~Settings() = default;

    QSettings* m_settings;
    
    int m_maxHistoryEntries = 500;
    int m_retentionDays = 7;
    int m_maxStorageMb = 250;
    int m_maxPayloadSizeKb = 10240;
    int m_maxImagePixels = 8000*8000;
    QString m_shortcutCapture = "Alt+Shift+S";
    QString m_shortcutHistory = "Alt+H";
    bool m_monitoringEnabled = false;
    bool m_autostartEnabled = false;
};
