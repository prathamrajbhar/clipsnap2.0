#pragma once
#include <QObject>
#include <QString>
#include "capability/CapabilityDetector.h"

class DoctorCommand : public QObject {
    Q_OBJECT
public:
    explicit DoctorCommand(const Capabilities& caps, QObject* parent = nullptr);
    void run();

private:
    void checkSection(const QString& name);
    void pass(const QString& item);
    void fail(const QString& item, const QString& remedy);
    void warn(const QString& item, const QString& detail);
    void info(const QString& item, const QString& detail);
    Capabilities m_caps;
};
