#ifndef BLV_LOG_LEVELS
#define BLV_LOG_LEVELS

#define BLV_DEBUG_L "DEBUG"
#define BLV_INFO_L "INFO"
#define BLV_NOTICE_L "NOTICE"
#define BLV_WARN_L "WARN"
#define BLV_ERROR_L "ERROR"
#define BLV_CRIT_L "CRIT"
#define BLV_ALERT_L "ALERT"
#define BLV_FATAL_L "FATAL"

#define BLV_ALWAYS_VISIBLE \
    BLV_DEBUG_L, \
    BLV_INFO_L, \
    BLV_NOTICE_L, \
    BLV_WARN_L, \
    BLV_ERROR_L

#endif

#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "entriesModel.h"

#include <QSet>
#include <QTextStream>

class Parser {
private:
    QVector<LogEntry> entries;
    QVector<QString> levelLabels;
    QSet<QString> moduleLabels;

public:
    Parser();

    const QVector<LogEntry> &getEntries() const;
    const QVector<QString> &getLevelLables() const;
    const QSet<QString> &getModuleLables() const;
    bool parse(QTextStream &logContents);
};

#endif // CONTROLLER_H
