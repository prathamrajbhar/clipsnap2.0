#pragma once

#include <QObject>
#include <QSqlDatabase>
#include <QString>
#include "HistoryItem.h"

class HistoryRepository : public QObject {
    Q_OBJECT
public:
    explicit HistoryRepository(QObject* parent = nullptr);
    ~HistoryRepository();

    bool open(const QString& dbPath);
    qint64 addItem(const HistoryItem& item);
    bool pinItem(qint64 id, bool pinned);
    bool deleteItem(qint64 id);
    bool clearUnpinned();
    bool clearAll();
    
    QList<HistoryItem> search(const QString& query, const QString& filter = "all", int limit = 100);
    QList<HistoryItem> recentItems(int limit = 50);
    HistoryItem itemById(qint64 id);
    
    void runEviction();
    bool restoreToClipboard(qint64 id);

signals:
    void itemAdded(qint64 id);
    void itemChanged(qint64 id);
    void itemRemoved(qint64 id);
    void historyCleared();
    void storageWarning(QString msg);

private:
    QSqlDatabase m_db;
    bool createSchema();
    void deletePayloads(qint64 id);
};
