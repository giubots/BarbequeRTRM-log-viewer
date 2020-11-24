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
    QString getName() const;
    QColor getColor();
    static LogLevel fromString(const QString &string);
    friend QDataStream &operator<<(QDataStream &stream, const LogLevel &level) {return stream << level.name;}
    bool operator==(const LogLevel &other) const {return name == (other.name);}
    friend uint qHash(const LogLevel &level, uint seed = 0) {return ::qHash(level.name, seed);}
private:
    LogLevel(QString name, QColor color);
};



struct LogEntry {
    QDateTime dateTime;
    LogLevel level;
    QString module;
    QString text;

    friend QDataStream &operator<<(QDataStream &stream, const LogEntry &entry) {
        return stream << entry.dateTime << entry.level << entry.module << entry.text;
    }
    QString toString() const;
};

class Filter {
public:
    QDateTime startDateTime;
    QDateTime endDateTime;
    QSet<LogLevel> levels;
    QSet<QString> modules;
    QString text;
public:
    Filter();
    Filter& since(QDateTime startDateTime);
    Filter& until(QDateTime endDateTime);
    Filter& onlyLevels(QSet<LogLevel> levels);
    Filter& addLevel(LogLevel level);
    Filter& removeLevel(LogLevel level);
    Filter& onlyModules(QSet<QString> modules);
    Filter& contains(QString text);
};

#endif // DATAMODEL_H
