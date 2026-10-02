#include "HistoryItem.h"

bool HistoryItem::isImage() const {
    for (const auto& rep : representations) {
        if (rep.mimeType.startsWith("image/")) {
            return true;
        }
    }
    return false;
}

bool HistoryItem::isText() const {
    for (const auto& rep : representations) {
        if (rep.mimeType.startsWith("text/")) {
            return true;
        }
    }
    return false;
}

QString HistoryItem::displayText() const {
    if (isText() && !searchableText.isEmpty()) {
        QString text = searchableText;
        if (text.length() > 100) {
            text = text.left(100) + "...";
        }
        return text;
    }
    if (isImage()) {
        return "[Image]";
    }
    return "[Unknown Content]";
}
