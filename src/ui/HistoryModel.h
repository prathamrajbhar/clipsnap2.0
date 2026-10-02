#pragma once

#include <QAbstractListModel>

class HistoryRepository;

class HistoryModel : public QAbstractListModel {
    Q_OBJECT
    Q_PROPERTY(int itemCount READ rowCount NOTIFY countChanged)

public:
    enum Roles {
        IdRole = Qt::UserRole + 1,
        DisplayTextRole,
        IsImageRole,
        ThumbnailPathRole,
        TimestampRole,
        SizeStrRole,
        PinnedRole,
        OriginRole
    };

    explicit HistoryModel(HistoryRepository* repo, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void search(const QString& query, const QString& filter);
    Q_INVOKABLE void restoreItem(qint64 id);
    Q_INVOKABLE void deleteItem(qint64 id);
    Q_INVOKABLE void togglePin(qint64 id);
    Q_INVOKABLE void clearAll();
    Q_INVOKABLE void clearUnpinned();

signals:
    void countChanged();

private:
    void reload(const QString& query = QString(), const QString& filter = QStringLiteral("all"));

    HistoryRepository* m_repo = nullptr;
    // Cache of current visible items
    struct CachedItem {
        qint64 id;
        QString displayText;
        bool isImage;
        QString thumbnailPath;
        QString timestamp;
        QString sizeStr;
        bool pinned;
        QString origin;
    };
    QList<CachedItem> m_items;
    QString m_currentQuery;
    QString m_currentFilter{ QStringLiteral("all") };
    bool m_suppressNext = false;
};
