#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <QDateTime>
#include <QString>
#include <QSet>
#include <QColor>

class LogLevel {
public:
    static const LogLevel INFO, NOTICE, WARN, ERROR, CRIT, ALERT, FATAL;
    QString getName() {return this->name;}
    QColor getColor() {return this->color;}
    friend QDataStream &operator<<(QDataStream &stream, const LogLevel &level) {return stream << level.name;}
private:
    QString name;
    QColor color;
    LogLevel(QString name, QColor color) : name(name), color(color) {};
};

//const LogLevel LogLevel::INFO = LogLevel("INFO", Qt::green);
//const LogLevel LogLevel::NOTICE = LogLevel("NOTICE", Qt::blue);
//const LogLevel LogLevel::WARN = LogLevel("NOTICE", Qt::yellow);
//const LogLevel LogLevel::ERROR = LogLevel("ERROR", Qt::darkRed);
//const LogLevel LogLevel::CRIT = LogLevel("CRIT", Qt::darkRed);
//const LogLevel LogLevel::ALERT = LogLevel("ALERT", Qt::darkYellow);
//const LogLevel LogLevel::FATAL = LogLevel("FATAL", Qt::red);

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
