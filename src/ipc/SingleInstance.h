#pragma once

#include <QObject>
#include <QStringList>
#include <QLocalServer>

class SingleInstance : public QObject {
    Q_OBJECT
public:
    explicit SingleInstance(QObject* parent = nullptr);
    ~SingleInstance();

    bool isPrimary() const;
    void sendCommand(const QStringList& args);

signals:
    void commandReceived(QStringList args);

private slots:
    void handleNewConnection();

private:
    QString getSocketName() const;
    QLocalServer* m_server;
    bool m_isPrimary;
};
