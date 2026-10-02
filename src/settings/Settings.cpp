#include "Settings.h"
#include <QStandardPaths>
#include <QDir>
#include <QCoreApplication>

Settings* Settings::instance() {
    static Settings s_instance;
    return &s_instance;
}

Settings::Settings(QObject* parent) : QObject(parent) {
    QString confPath = configDir() + "/clipsnap.ini";
    m_settings = new QSettings(confPath, QSettings::IniFormat, this);
    
    m_maxHistoryEntries = m_settings->value("maxHistoryEntries", 500).toInt();
    m_retentionDays = m_settings->value("retentionDays", 7).toInt();
    m_maxStorageMb = m_settings->value("maxStorageMb", 250).toInt();
    m_maxPayloadSizeKb = m_settings->value("maxPayloadSizeKb", 10240).toInt();
    m_maxImagePixels = m_settings->value("maxImagePixels", 8000*8000).toInt();
    m_shortcutCapture = m_settings->value("shortcutCapture", "Alt+Shift+S").toString();
    m_shortcutHistory = m_settings->value("shortcutHistory", "Alt+H").toString();
    m_monitoringEnabled = m_settings->value("monitoringEnabled", true).toBool();
    m_autostartEnabled = m_settings->value("autostartEnabled", true).toBool();
}

QString Settings::configDir() const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppConfigLocation);
    QDir().mkpath(path);
    return path;
}

QString Settings::dataDir() const {
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QDir().mkpath(path);
    return path;
}

QString Settings::stateDir() const {
    // Qt 6.2 doesn't have AppStateLocation easily mapped on all platforms, but standard AppData is okay,
    // or use QStandardPaths::GenericDataLocation
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/state";
    QDir().mkpath(path);
    return path;
}

int Settings::maxHistoryEntries() const { return m_maxHistoryEntries; }
void Settings::setMaxHistoryEntries(int value) {
    if (m_maxHistoryEntries != value) {
        m_maxHistoryEntries = value;
        m_settings->setValue("maxHistoryEntries", value);
        emit maxHistoryEntriesChanged();
    }
}

int Settings::retentionDays() const { return m_retentionDays; }
void Settings::setRetentionDays(int value) {
    if (m_retentionDays != value) {
        m_retentionDays = value;
        m_settings->setValue("retentionDays", value);
        emit retentionDaysChanged();
    }
}

int Settings::maxStorageMb() const { return m_maxStorageMb; }
void Settings::setMaxStorageMb(int value) {
    if (m_maxStorageMb != value) {
        m_maxStorageMb = value;
        m_settings->setValue("maxStorageMb", value);
        emit maxStorageMbChanged();
    }
}

int Settings::maxPayloadSizeKb() const { return m_maxPayloadSizeKb; }
void Settings::setMaxPayloadSizeKb(int value) {
    if (m_maxPayloadSizeKb != value) {
        m_maxPayloadSizeKb = value;
        m_settings->setValue("maxPayloadSizeKb", value);
        emit maxPayloadSizeKbChanged();
    }
}

int Settings::maxImagePixels() const { return m_maxImagePixels; }
void Settings::setMaxImagePixels(int value) {
    if (m_maxImagePixels != value) {
        m_maxImagePixels = value;
        m_settings->setValue("maxImagePixels", value);
        emit maxImagePixelsChanged();
    }
}

QString Settings::shortcutCapture() const { return m_shortcutCapture; }
void Settings::setShortcutCapture(const QString& value) {
    if (m_shortcutCapture != value) {
        m_shortcutCapture = value;
        m_settings->setValue("shortcutCapture", value);
        emit shortcutCaptureChanged();
    }
}

QString Settings::shortcutHistory() const { return m_shortcutHistory; }
void Settings::setShortcutHistory(const QString& value) {
    if (m_shortcutHistory != value) {
        m_shortcutHistory = value;
        m_settings->setValue("shortcutHistory", value);
        emit shortcutHistoryChanged();
    }
}

bool Settings::monitoringEnabled() const { return m_monitoringEnabled; }
void Settings::setMonitoringEnabled(bool value) {
    if (m_monitoringEnabled != value) {
        m_monitoringEnabled = value;
        m_settings->setValue("monitoringEnabled", value);
        emit monitoringEnabledChanged();
    }
}

bool Settings::autostartEnabled() const { return m_autostartEnabled; }
void Settings::setAutostartEnabled(bool value) {
    if (m_autostartEnabled != value) {
        m_autostartEnabled = value;
        m_settings->setValue("autostartEnabled", value);
        emit autostartEnabledChanged();
    }
}
