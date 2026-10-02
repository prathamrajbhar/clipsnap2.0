#pragma once
#include <QString>
#include <QtGlobal>

class Logger {
public:
    static void init();
    static QString logFilePath();
    static void printRecentLogs(int maxLines = 100);
    static void clearLogs();

private:
    static void messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg);
};
