#include "AppController.h"

AppController::AppController(QObject* parent)
    : QObject(parent)
{
}

bool AppController::monitoringActive() const
{
    return m_monitoringActive;
}

void AppController::openSettings()
{
    emit settingsRequested();
}

void AppController::requestCapture()
{
    emit captureRequested();
}

void AppController::pauseMonitoring()
{
    if (m_monitoringActive) {
        m_monitoringActive = false;
        emit monitoringActiveChanged();
    }
}

void AppController::resumeMonitoring()
{
    if (!m_monitoringActive) {
        m_monitoringActive = true;
        emit monitoringActiveChanged();
    }
}

void AppController::toggleMonitoring()
{
    if (m_monitoringActive) {
        pauseMonitoring();
    } else {
        resumeMonitoring();
    }
}

void AppController::checkActiveClipboard()
{
    emit clipboardCheckRequested();
}
