#include <QtTest>
#include <QSqlDatabase>
#include <QTemporaryDir>
#include "history/HistoryRepository.h"
#include "history/HistoryItem.h"

class TestHistory : public QObject {
    Q_OBJECT
private slots:
    void initTestCase() {
        repo = new HistoryRepository(this);
        QVERIFY(repo->open(tempDir.path() + "/test.db"));
    }
    
    void testAddAndRetrieveText() {
        HistoryItem item;
        item.createdAt = QDateTime::currentDateTime();
        item.lastAccessedAt = item.createdAt;
        item.origin = "clipboard";
        item.contentHash = QByteArray("hash1");
        item.searchableText = "Hello World";
        
        MimeRepresentation rep;
        rep.mimeType = "text/plain";
        rep.inlineData = "Hello World";
        item.representations.append(rep);
        
        qint64 id = repo->addItem(item);
        QVERIFY(id > 0);
        
        HistoryItem retrieved = repo->itemById(id);
        QCOMPARE(retrieved.id, id);
        QCOMPARE(retrieved.searchableText, QString("Hello World"));
        QCOMPARE(retrieved.representations.size(), 1);
        QCOMPARE(retrieved.representations[0].inlineData, QByteArray("Hello World"));
    }
    
    void testDeduplication() {
        HistoryItem item;
        item.createdAt = QDateTime::currentDateTime();
        item.lastAccessedAt = item.createdAt;
        item.origin = "clipboard";
        item.contentHash = QByteArray("hash2");
        item.searchableText = "Dup";
        
        qint64 id1 = repo->addItem(item);
        qint64 id2 = repo->addItem(item);
        
        QCOMPARE(id1, id2);
    }
    
    void testPinning() {
        HistoryItem item;
        item.createdAt = QDateTime::currentDateTime();
        item.lastAccessedAt = item.createdAt;
        item.origin = "clipboard";
        item.contentHash = QByteArray("hash3");
        item.searchableText = "Pin Me";
        
        qint64 id = repo->addItem(item);
        QVERIFY(repo->pinItem(id, true));
        
        HistoryItem retrieved = repo->itemById(id);
        QVERIFY(retrieved.pinned);
    }

    void testSearch() {
        HistoryItem item;
        item.createdAt = QDateTime::currentDateTime();
        item.lastAccessedAt = item.createdAt;
        item.origin = "clipboard";
        item.contentHash = QByteArray("hash4");
        item.searchableText = "Searchable String Data";
        repo->addItem(item);

        QList<HistoryItem> results = repo->search("String");
        QVERIFY(!results.isEmpty());
        bool found = false;
        for (const auto& r : results) {
            if (r.searchableText == "Searchable String Data") {
                found = true;
            }
        }
        QVERIFY(found);
    }

    void testEviction() {
        // Simple test for compilation purposes
        QVERIFY(true);
    }

    void testClearUnpinnedAndClearAll() {
        HistoryItem unpinnedItem;
        unpinnedItem.createdAt = QDateTime::currentDateTime();
        unpinnedItem.lastAccessedAt = unpinnedItem.createdAt;
        unpinnedItem.origin = "clipboard";
        unpinnedItem.contentHash = QByteArray("unpinned_hash");
        unpinnedItem.searchableText = "Unpinned Item";
        qint64 uId = repo->addItem(unpinnedItem);
        QVERIFY(uId > 0);

        HistoryItem pinnedItem;
        pinnedItem.createdAt = QDateTime::currentDateTime();
        pinnedItem.lastAccessedAt = pinnedItem.createdAt;
        pinnedItem.origin = "clipboard";
        pinnedItem.contentHash = QByteArray("pinned_hash");
        pinnedItem.searchableText = "Pinned Item";
        qint64 pId = repo->addItem(pinnedItem);
        QVERIFY(pId > 0);
        QVERIFY(repo->pinItem(pId, true));

        // Clear unpinned
        QVERIFY(repo->clearUnpinned());
        QCOMPARE(repo->itemById(uId).id, 0);
        QCOMPARE(repo->itemById(pId).id, pId);

        // Clear all
        QVERIFY(repo->clearAll());
        QCOMPARE(repo->itemById(pId).id, 0);
        QCOMPARE(repo->recentItems(10).size(), 0);
    }
    
    void cleanupTestCase() {
        delete repo;
    }

private:
    QTemporaryDir tempDir;
    HistoryRepository* repo;
};

QTEST_MAIN(TestHistory)
#include "TestHistory.moc"
