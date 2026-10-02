#include "Logger.h"
#include "../settings/Settings.h"
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDateTime>
#include <QMutex>
#include <QFileInfo>
#include <iostream>

static QMutex s_logMutex;

QString Logger::logFilePath() {
    QString dir = Settings::instance()->stateDir();
    return dir + "/clipsnap.log";
}

void Logger::init() {
    qInstallMessageHandler(Logger::messageHandler);
}

void Logger::messageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    Q_UNUSED(context);

    QString levelStr;
    switch (type) {
    case QtDebugMsg:
        levelStr = "DEBUG";
        break;
    case QtInfoMsg:
        levelStr = "INFO";
        break;
    case QtWarningMsg:
        levelStr = "WARN";
        break;
    case QtCriticalMsg:
        levelStr = "CRITICAL";
        break;
    case QtFatalMsg:
        levelStr = "FATAL";
        break;
    }

    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss.zzz");
    QString formatted = QString("[%1] [%2] %3\n").arg(timestamp, levelStr, msg);

    // Also write to stdout/stderr for terminal runs
    if (type == QtWarningMsg || type == QtCriticalMsg || type == QtFatalMsg) {
        std::cerr << formatted.toStdString();
    } else {
        std::cout << formatted.toStdString();
    }

    // Write to persistent log file with rotation
    QMutexLocker locker(&s_logMutex);
    QString path = logFilePath();
    QFile file(path);

    // Rotate if larger than 2MB
    if (file.exists() && file.size() > 2 * 1024 * 1024) {
        QString backupPath = path + ".1";
        QFile::remove(backupPath);
        QFile::rename(path, backupPath);
    }

    if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
        QTextStream stream(&file);
        stream << formatted;
        file.close();
    }
}

void Logger::printRecentLogs(int maxLines) {
    QString path = logFilePath();
    QFile file(path);
    if (!file.exists() || !file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "No log file found at " << path.toStdString() << "\n";
        return;
    }

    QTextStream stream(&file);
    QStringList lines;
    while (!stream.atEnd()) {
        lines.append(stream.readLine());
    }
    file.close();

    int start = qMax(0, lines.size() - maxLines);
    std::cout << "--- ClipSnap Logs (" << path.toStdString() << ") ---\n";
    for (int i = start; i < lines.size(); ++i) {
        std::cout << lines.at(i).toStdString() << "\n";
    }
}

void Logger::clearLogs() {
    QFile::remove(logFilePath());
    QFile::remove(logFilePath() + ".1");
}
