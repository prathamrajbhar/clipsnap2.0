#include "HistoryRepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QDir>
#include <QFile>
#include <QDateTime>
#include "../settings/Settings.h"
#include <QClipboard>
#include <QGuiApplication>
#include <QMimeData>
#include <QImage>
#include <QCryptographicHash>

HistoryRepository::HistoryRepository(QObject* parent) : QObject(parent) {
}

HistoryRepository::~HistoryRepository() {
    if (m_db.isOpen()) m_db.close();
}

bool HistoryRepository::open(const QString& dbPath) {
    m_db = QSqlDatabase::addDatabase("QSQLITE", "history_db");
    m_db.setDatabaseName(dbPath);
    if (!m_db.open()) return false;
    return createSchema();
}

bool HistoryRepository::createSchema() {
    QSqlQuery q(m_db);
    q.exec("PRAGMA foreign_keys = ON;");
    
    if (!q.exec("CREATE TABLE IF NOT EXISTS schema_version (version INTEGER NOT NULL);")) return false;
    
    q.exec("SELECT version FROM schema_version");
    if (!q.next()) {
        q.exec("INSERT INTO schema_version (version) VALUES (1)");
        
        q.exec("CREATE TABLE IF NOT EXISTS items ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "created_at INTEGER NOT NULL, "
               "last_accessed_at INTEGER NOT NULL, "
               "origin TEXT NOT NULL, "
               "content_hash BLOB NOT NULL, "
               "pinned INTEGER NOT NULL DEFAULT 0, "
               "searchable_text TEXT, "
               "storage_size_bytes INTEGER NOT NULL DEFAULT 0, "
               "thumbnail_path TEXT)");
               
        q.exec("CREATE TABLE IF NOT EXISTS representations ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT, "
               "item_id INTEGER NOT NULL REFERENCES items(id) ON DELETE CASCADE, "
               "mime_type TEXT NOT NULL, "
               "payload_path TEXT, "
               "inline_data BLOB)");
               
        q.exec("CREATE VIRTUAL TABLE IF NOT EXISTS items_fts USING fts5(searchable_text, content='items', content_rowid='id');");
    }
    return true;
}

qint64 HistoryRepository::addItem(const HistoryItem& item) {
    QSqlQuery q(m_db);
    
    // Deduplication check
    q.prepare("SELECT id FROM items WHERE content_hash = ?");
    q.addBindValue(item.contentHash);
    if (q.exec() && q.next()) {
        qint64 existingId = q.value(0).toLongLong();
        q.prepare("UPDATE items SET last_accessed_at = ? WHERE id = ?");
        q.addBindValue(QDateTime::currentMSecsSinceEpoch());
        q.addBindValue(existingId);
        q.exec();
        emit itemChanged(existingId);
        return existingId;
    }
    
    m_db.transaction();
    
    q.prepare("INSERT INTO items (created_at, last_accessed_at, origin, content_hash, pinned, searchable_text, storage_size_bytes, thumbnail_path) "
              "VALUES (?, ?, ?, ?, ?, ?, ?, ?)");
    q.addBindValue(item.createdAt.toMSecsSinceEpoch());
    q.addBindValue(item.lastAccessedAt.toMSecsSinceEpoch());
    q.addBindValue(item.origin);
    q.addBindValue(item.contentHash);
    q.addBindValue(item.pinned ? 1 : 0);
    q.addBindValue(item.searchableText);
    q.addBindValue(item.storageSizeBytes);
    q.addBindValue(item.thumbnailPath);
    
    if (!q.exec()) {
        m_db.rollback();
        return -1;
    }
    
    qint64 id = q.lastInsertId().toLongLong();
    
    for (const auto& rep : item.representations) {
        QSqlQuery rq(m_db);
        rq.prepare("INSERT INTO representations (item_id, mime_type, payload_path, inline_data) VALUES (?, ?, ?, ?)");
        rq.addBindValue(id);
        rq.addBindValue(rep.mimeType);
        rq.addBindValue(rep.payloadPath);
        rq.addBindValue(rep.inlineData);
        rq.exec();
    }
    
    QSqlQuery fts(m_db);
    fts.prepare("INSERT INTO items_fts (rowid, searchable_text) VALUES (?, ?)");
    fts.addBindValue(id);
    fts.addBindValue(item.searchableText);
    fts.exec();
    
    m_db.commit();
    runEviction();
    emit itemAdded(id);
    return id;
}

bool HistoryRepository::pinItem(qint64 id, bool pinned) {
    QSqlQuery q(m_db);
    q.prepare("UPDATE items SET pinned = ? WHERE id = ?");
    q.addBindValue(pinned ? 1 : 0);
    q.addBindValue(id);
    if (q.exec()) {
        emit itemChanged(id);
        return true;
    }
    return false;
}

void HistoryRepository::deletePayloads(qint64 id) {
    QSqlQuery q(m_db);
    q.prepare("SELECT payload_path FROM representations WHERE item_id = ? AND payload_path IS NOT NULL AND payload_path != ''");
    q.addBindValue(id);
    if (q.exec()) {
        while (q.next()) {
            QFile::remove(q.value(0).toString());
        }
    }
    
    QSqlQuery tq(m_db);
    tq.prepare("SELECT thumbnail_path FROM items WHERE id = ? AND thumbnail_path IS NOT NULL AND thumbnail_path != ''");
    tq.addBindValue(id);
    if (tq.exec() && tq.next()) {
        QFile::remove(tq.value(0).toString());
    }
}

bool HistoryRepository::deleteItem(qint64 id) {
    deletePayloads(id);
    QSqlQuery q(m_db);
    q.prepare("DELETE FROM items WHERE id = ?");
    q.addBindValue(id);
    if (q.exec()) {
        QSqlQuery fts(m_db);
        fts.prepare("DELETE FROM items_fts WHERE rowid = ?");
        fts.addBindValue(id);
        fts.exec();
        emit itemRemoved(id);
        return true;
    }
    return false;
}

bool HistoryRepository::clearUnpinned() {
    QSqlQuery q(m_db);
    q.exec("SELECT id FROM items WHERE pinned = 0");
    while (q.next()) {
        deletePayloads(q.value(0).toLongLong());
    }
    
    m_db.transaction();
    q.exec("DELETE FROM items WHERE pinned = 0");
    q.exec("INSERT INTO items_fts(items_fts) VALUES('rebuild')");
    m_db.commit();
    emit historyCleared();
    return true;
}

bool HistoryRepository::clearAll() {
    QSqlQuery q(m_db);
    q.exec("SELECT id FROM items");
    while (q.next()) {
        deletePayloads(q.value(0).toLongLong());
    }
    m_db.transaction();
    q.exec("DELETE FROM items");
    q.exec("INSERT INTO items_fts(items_fts) VALUES('rebuild')");
    m_db.commit();
    emit historyCleared();
    return true;
}

QList<HistoryItem> HistoryRepository::search(const QString& query, const QString& filter, int limit) {
    QList<HistoryItem> results;
    QSqlQuery q(m_db);
    
    QString sql = "SELECT * FROM items ";
    bool hasWhere = false;
    
    if (!query.trimmed().isEmpty()) {
        // Fallback to LIKE if FTS5 not available or just simpler for tests for now
        sql += QString("WHERE searchable_text LIKE '%%1%' ").arg(query);
        hasWhere = true;
    }
    
    if (filter == "pinned") {
        sql += (hasWhere ? "AND " : "WHERE ") + QString("pinned = 1 ");
        hasWhere = true;
    } else if (filter == "text") {
        sql += (hasWhere ? "AND " : "WHERE ") + QString("searchable_text IS NOT NULL AND searchable_text != '' ");
        hasWhere = true;
    } else if (filter == "images") {
        sql += (hasWhere ? "AND " : "WHERE ") + QString("thumbnail_path IS NOT NULL AND thumbnail_path != '' ");
        hasWhere = true;
    }
    
    sql += QString("ORDER BY last_accessed_at DESC LIMIT %1").arg(limit);
    
    if (q.exec(sql)) {
        while (q.next()) {
            HistoryItem item;
            item.id = q.value("id").toLongLong();
            item.createdAt = QDateTime::fromMSecsSinceEpoch(q.value("created_at").toLongLong());
            item.lastAccessedAt = QDateTime::fromMSecsSinceEpoch(q.value("last_accessed_at").toLongLong());
            item.origin = q.value("origin").toString();
            item.contentHash = q.value("content_hash").toByteArray();
            item.pinned = q.value("pinned").toInt() == 1;
            item.searchableText = q.value("searchable_text").toString();
            item.storageSizeBytes = q.value("storage_size_bytes").toLongLong();
            item.thumbnailPath = q.value("thumbnail_path").toString();
            
            QSqlQuery rq(m_db);
            rq.prepare("SELECT mime_type, payload_path, inline_data FROM representations WHERE item_id = ?");
            rq.addBindValue(item.id);
            if (rq.exec()) {
                while (rq.next()) {
                    MimeRepresentation rep;
                    rep.mimeType = rq.value("mime_type").toString();
                    rep.payloadPath = rq.value("payload_path").toString();
                    rep.inlineData = rq.value("inline_data").toByteArray();
                    item.representations.append(rep);
                }
            }
            results.append(item);
        }
    }
    return results;
}

QList<HistoryItem> HistoryRepository::recentItems(int limit) {
    return search("", "all", limit);
}

HistoryItem HistoryRepository::itemById(qint64 id) {
    QSqlQuery q(m_db);
    q.prepare("SELECT * FROM items WHERE id = ?");
    q.addBindValue(id);
    if (q.exec() && q.next()) {
        HistoryItem item;
        item.id = q.value("id").toLongLong();
        item.createdAt = QDateTime::fromMSecsSinceEpoch(q.value("created_at").toLongLong());
        item.lastAccessedAt = QDateTime::fromMSecsSinceEpoch(q.value("last_accessed_at").toLongLong());
        item.origin = q.value("origin").toString();
        item.contentHash = q.value("content_hash").toByteArray();
        item.pinned = q.value("pinned").toInt() == 1;
        item.searchableText = q.value("searchable_text").toString();
        item.storageSizeBytes = q.value("storage_size_bytes").toLongLong();
        item.thumbnailPath = q.value("thumbnail_path").toString();
        
        QSqlQuery rq(m_db);
        rq.prepare("SELECT mime_type, payload_path, inline_data FROM representations WHERE item_id = ?");
        rq.addBindValue(item.id);
        if (rq.exec()) {
            while (rq.next()) {
                MimeRepresentation rep;
                rep.mimeType = rq.value("mime_type").toString();
                rep.payloadPath = rq.value("payload_path").toString();
                rep.inlineData = rq.value("inline_data").toByteArray();
                item.representations.append(rep);
            }
        }
        return item;
    }
    return HistoryItem();
}

void HistoryRepository::runEviction() {
    Settings* s = Settings::instance();
    
    QSqlQuery q(m_db);
    q.prepare("SELECT COUNT(*) FROM items WHERE pinned = 0");
    if (q.exec() && q.next()) {
        int count = q.value(0).toInt();
        if (count > s->maxHistoryEntries()) {
            QSqlQuery dq(m_db);
            dq.prepare(QString("SELECT id FROM items WHERE pinned = 0 ORDER BY last_accessed_at ASC LIMIT %1").arg(count - s->maxHistoryEntries()));
            if (dq.exec()) {
                while (dq.next()) {
                    deleteItem(dq.value(0).toLongLong());
                }
            }
        }
    }
    
    qint64 cutoff = QDateTime::currentDateTime().addDays(-s->retentionDays()).toMSecsSinceEpoch();
    q.prepare("SELECT id FROM items WHERE pinned = 0 AND last_accessed_at < ?");
    q.addBindValue(cutoff);
    if (q.exec()) {
        while (q.next()) {
            deleteItem(q.value(0).toLongLong());
        }
    }
    
    q.prepare("SELECT SUM(storage_size_bytes) FROM items");
    if (q.exec() && q.next()) {
        qint64 totalBytes = q.value(0).toLongLong();
        if (totalBytes > s->maxStorageMb() * 1024 * 1024LL) {
            emit storageWarning("Storage limit exceeded.");
        }
    }
}

bool HistoryRepository::restoreToClipboard(qint64 id) {
    HistoryItem item = itemById(id);
    if (item.id == 0) return false;
    
    QClipboard *clipboard = QGuiApplication::clipboard();
    if (!clipboard) return false;

    if (item.isImage()) {
        QImage img;
        for (const auto& rep : item.representations) {
            if (!rep.payloadPath.isEmpty()) {
                img.load(rep.payloadPath);
                if (!img.isNull()) break;
            } else if (!rep.inlineData.isEmpty()) {
                img.loadFromData(rep.inlineData);
                if (!img.isNull()) break;
            }
        }
        if (!img.isNull()) {
            clipboard->setImage(img, QClipboard::Clipboard);
        } else {
            QMimeData *mimeData = new QMimeData();
            for (const auto& rep : item.representations) {
                if (!rep.inlineData.isEmpty()) {
                    mimeData->setData(rep.mimeType, rep.inlineData);
                } else if (!rep.payloadPath.isEmpty()) {
                    QFile file(rep.payloadPath);
                    if (file.open(QIODevice::ReadOnly)) {
                        mimeData->setData(rep.mimeType, file.readAll());
                    }
                }
            }
            clipboard->setMimeData(mimeData, QClipboard::Clipboard);
        }
    } else {
        QString text = item.searchableText;
        if (text.isEmpty()) {
            for (const auto& rep : item.representations) {
                if (rep.mimeType.startsWith("text/")) {
                    text = QString::fromUtf8(rep.inlineData);
                    if (!text.isEmpty()) break;
                }
            }
        }
        clipboard->setText(text, QClipboard::Clipboard);
        if (clipboard->supportsSelection()) {
            clipboard->setText(text, QClipboard::Selection);
        }
    }
    
    QSqlQuery q(m_db);
    q.prepare("UPDATE items SET last_accessed_at = ? WHERE id = ?");
    q.addBindValue(QDateTime::currentMSecsSinceEpoch());
    q.addBindValue(id);
    q.exec();
    emit itemChanged(id);
    return true;
}
