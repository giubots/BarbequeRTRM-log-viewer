#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QDateTime>
#include <QString>
#include <QSet>
#include <QColor>

class LogLevel {
public:
    static const LogLevel DEBUG, INFO, NOTICE, WARN, ERROR, CRIT, ALERT, FATAL;
    static const LogLevel values[];
private:
    QString name;
    QColor color;
public:
    QString getName();
    QColor getColor();
    static LogLevel fromString(const QString &string);
    friend QDataStream &operator<<(QDataStream &stream, const LogLevel &level) {return stream << level.name;}
private:
    LogLevel(QString name, QColor color);
};



struct LogEntry {
    QDateTime dateTime;
    LogLevel level;
    QString module;
    QString message;

    friend QDataStream &operator<<(QDataStream &stream, const LogEntry &entry) {
        return stream << entry.dateTime << entry.level << entry.module << entry.message;
    }
};

struct Filter {
    QDateTime startDateTime;
    QDateTime endDateTime;
    QSet<LogLevel> levels;
    QSet<QString> modules;
    QString text;
};

#endif // DATAMODEL_H
