#include "SingleInstance.h"
#include <QCoreApplication>
#include <QLocalSocket>
#include <QJsonDocument>
#include <QJsonArray>
#include <QFile>

SingleInstance::SingleInstance(QObject* parent) : QObject(parent), m_server(nullptr), m_isPrimary(false) {
    QString socketName = getSocketName();
    
    QLocalSocket socket;
    socket.connectToServer(socketName);
    
    if (socket.waitForConnected(500)) {
        m_isPrimary = false;
        return;
    }
    
    QLocalServer::removeServer(socketName);
    
    m_server = new QLocalServer(this);
    m_server->setSocketOptions(QLocalServer::UserAccessOption);
    if (m_server->listen(socketName)) {
        m_isPrimary = true;
        connect(m_server, &QLocalServer::newConnection, this, &SingleInstance::handleNewConnection);
    }
}

SingleInstance::~SingleInstance() {
    if (m_isPrimary && m_server) {
        m_server->close();
        QLocalServer::removeServer(getSocketName());
    }
}

bool SingleInstance::isPrimary() const {
    return m_isPrimary;
}

#include <unistd.h>

QString SingleInstance::getSocketName() const {
    return "clipsnap_" + QString::number(::getuid());
}

void SingleInstance::sendCommand(const QStringList& args) {
    QLocalSocket socket;
    socket.connectToServer(getSocketName());
    if (socket.waitForConnected(1000)) {
        QJsonArray arr;
        for (const QString& arg : args) {
            arr.append(arg);
        }
        QJsonDocument doc(arr);
        socket.write(doc.toJson(QJsonDocument::Compact));
        socket.flush();
        socket.waitForBytesWritten(1000);
        // Wait for server to process and acknowledge or close
        socket.waitForReadyRead(500);
        socket.disconnectFromServer();
    }
}

void SingleInstance::handleNewConnection() {
    while (QLocalSocket* client = m_server->nextPendingConnection()) {
        auto processClient = [this, client]() {
            if (!client) return;
            QByteArray data = client->readAll();
            if (data.isEmpty()) return;
            QJsonDocument doc = QJsonDocument::fromJson(data);
            if (doc.isArray()) {
                QStringList args;
                for (const auto& val : doc.array()) {
                    args.append(val.toString());
                }
                emit commandReceived(args);
            }
            client->write("OK\n");
            client->flush();
        };

        connect(client, &QLocalSocket::readyRead, this, processClient);
        connect(client, &QLocalSocket::disconnected, this, [processClient, client]() {
            processClient();
            client->deleteLater();
        });

        if (client->bytesAvailable() > 0) {
            processClient();
        }
    }
}

