#include <headers/dataModel.h>

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


QString LogLevel::getName() const {return this->name;}

QColor LogLevel::getColor() {return this->color;}

LogLevel LogLevel::fromString(const QString &string) {
    for (LogLevel level : LogLevel::values)
        if (!level.name.compare(string))
            return level;
    qDebug() << "Level not found: " << string;
    return LogLevel(string.toUpper(), Qt::black);
}

Filter::Filter() :
    startDateTime(QDateTime()),
    endDateTime(QDateTime()),
    levels(QSet<LogLevel>()),
    modules(QSet<QString>()),
    text("") {}

Filter &Filter::since(QDateTime startDateTime) {
    this->startDateTime = startDateTime;
    return *this;
}

Filter &Filter::until(QDateTime endDateTime) {
    this->endDateTime = endDateTime;
    return *this;
}

Filter &Filter::onlyLevels(QSet<LogLevel> levels) {
    this->levels = levels;
    return *this;
}

Filter &Filter::onlyModules(QSet<QString> modules) {
    this->modules = modules;
    return *this;
}

Filter &Filter::contains(QString text) {
    this->text = text;
    return *this;
}

QString LogEntry::toString() const {
    return dateTime.toString(Qt::ISODateWithMs) + " " + level.getName() + " - " + module + " : " + text;
}
