#pragma once

#include <QString>
#include <QByteArray>
#include <QDateTime>
#include <QList>

struct MimeRepresentation {
    QString mimeType;
    QString payloadPath;
    QByteArray inlineData;
};

struct HistoryItem {
    qint64 id = 0;
    QDateTime createdAt;
    QDateTime lastAccessedAt;
    QString origin;
    QByteArray contentHash;
    bool pinned = false;
    QString searchableText;
    qint64 storageSizeBytes = 0;
    QList<MimeRepresentation> representations;
    QString thumbnailPath;

    bool isImage() const;
    bool isText() const;
    QString displayText() const;
};
