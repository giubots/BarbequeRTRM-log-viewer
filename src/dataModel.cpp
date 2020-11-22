#include <headers/dataModel.h>
#include <QString>
#include <QtDebug>

LogLevel::LogLevel(QString name, QColor color) : name(name), color(color) {};

const LogLevel LogLevel::DEBUG = LogLevel("DEBUG", Qt::black);
const LogLevel LogLevel::INFO = LogLevel("INFO", Qt::green);
const LogLevel LogLevel::NOTICE = LogLevel("NOTICE", Qt::blue);
const LogLevel LogLevel::WARN = LogLevel("WARN", Qt::yellow);
const LogLevel LogLevel::ERROR = LogLevel("ERROR", Qt::darkRed);
const LogLevel LogLevel::CRIT = LogLevel("CRIT", Qt::darkRed);
const LogLevel LogLevel::ALERT = LogLevel("ALERT", Qt::darkYellow);
const LogLevel LogLevel::FATAL = LogLevel("FATAL", Qt::red);
const LogLevel LogLevel::values[] = {LogLevel::DEBUG, LogLevel::INFO, LogLevel::NOTICE, LogLevel::WARN, LogLevel::ERROR, LogLevel::CRIT, LogLevel::ALERT, LogLevel::FATAL};

QString LogLevel::getName() {return this->name;}

QColor LogLevel::getColor() {return this->color;}

LogLevel LogLevel::fromString(const QString &string) {
    for (LogLevel level : LogLevel::values)
        if (!level.name.compare(string))
            return level;
    qDebug() << "Level not found: " << string;
    return LogLevel(string.toUpper(), Qt::black);
}
