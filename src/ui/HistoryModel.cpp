#include "HistoryModel.h"
#include "../history/HistoryRepository.h"
#include "../history/HistoryItem.h"
#include <QDateTime>
#include <QGuiApplication>
#include <QClipboard>

HistoryModel::HistoryModel(HistoryRepository* repo, QObject* parent)
    : QAbstractListModel(parent)
    , m_repo(repo)
{
    if (m_repo) {
        connect(m_repo, &HistoryRepository::itemAdded, this, [this](qint64) {
            reload(m_currentQuery, m_currentFilter);
        });
        connect(m_repo, &HistoryRepository::itemRemoved, this, [this](qint64) {
            reload(m_currentQuery, m_currentFilter);
        });
        connect(m_repo, &HistoryRepository::itemChanged, this, [this](qint64) {
            reload(m_currentQuery, m_currentFilter);
        });
        connect(m_repo, &HistoryRepository::historyCleared, this, [this]() {
            reload(m_currentQuery, m_currentFilter);
        });
        reload();
    }
}

void HistoryModel::reload(const QString& query, const QString& filter)
{
    beginResetModel();
    m_items.clear();

    QList<HistoryItem> items;
    if (query.isEmpty() && filter == QLatin1String("all")) {
        items = m_repo ? m_repo->recentItems(200) : QList<HistoryItem>{};
    } else {
        items = m_repo ? m_repo->search(query, filter, 200) : QList<HistoryItem>{};
    }

    for (const auto& item : items) {
        CachedItem ci;
        ci.id = item.id;
        ci.displayText = item.displayText();
        ci.isImage = item.isImage();
        ci.thumbnailPath = item.thumbnailPath;
        ci.timestamp = QLocale().toString(item.createdAt.toLocalTime(), QLocale::ShortFormat);
        // Format size
        if (item.storageSizeBytes < 1024) {
            ci.sizeStr = QString::number(item.storageSizeBytes) + " B";
        } else if (item.storageSizeBytes < 1024 * 1024) {
            ci.sizeStr = QString::number(item.storageSizeBytes / 1024) + " KB";
        } else {
            ci.sizeStr = QString::number(item.storageSizeBytes / (1024 * 1024)) + " MB";
        }
        ci.pinned = item.pinned;
        ci.origin = item.origin;
        m_items.append(ci);
    }

    endResetModel();
    emit countChanged();
}

int HistoryModel::rowCount(const QModelIndex& parent) const
{
    if (parent.isValid()) return 0;
    return m_items.size();
}

QVariant HistoryModel::data(const QModelIndex& index, int role) const
{
    if (!index.isValid() || index.row() >= m_items.size()) return QVariant();
    const auto& item = m_items.at(index.row());

    switch (role) {
    case IdRole:          return item.id;
    case DisplayTextRole: return item.displayText;
    case IsImageRole:     return item.isImage;
    case ThumbnailPathRole: return item.thumbnailPath;
    case TimestampRole:   return item.timestamp;
    case SizeStrRole:     return item.sizeStr;
    case PinnedRole:      return item.pinned;
    case OriginRole:      return item.origin;
    default:              return QVariant();
    }
}

QHash<int, QByteArray> HistoryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[IdRole]           = "id";
    roles[DisplayTextRole]  = "displayText";
    roles[IsImageRole]      = "isImage";
    roles[ThumbnailPathRole]= "thumbnailPath";
    roles[TimestampRole]    = "timestamp";
    roles[SizeStrRole]      = "sizeStr";
    roles[PinnedRole]       = "pinned";
    roles[OriginRole]       = "origin";
    return roles;
}

void HistoryModel::search(const QString& query, const QString& filter)
{
    m_currentQuery = query;
    m_currentFilter = filter;
    reload(query, filter);
}

void HistoryModel::restoreItem(qint64 id)
{
    if (!m_repo) return;
    m_suppressNext = true;
    m_repo->restoreToClipboard(id);
}

void HistoryModel::deleteItem(qint64 id)
{
    if (!m_repo) return;
    m_repo->deleteItem(id);
}

void HistoryModel::togglePin(qint64 id)
{
    if (!m_repo) return;
    // Find current pin state
    for (const auto& item : m_items) {
        if (item.id == id) {
            m_repo->pinItem(id, !item.pinned);
            return;
        }
    }
}

void HistoryModel::clearAll()
{
    if (!m_repo) return;
    m_repo->clearAll();
}

void HistoryModel::clearUnpinned()
{
    if (!m_repo) return;
    m_repo->clearUnpinned();
}
