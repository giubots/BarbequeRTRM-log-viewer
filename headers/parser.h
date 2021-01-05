/*
 * Copyright (C) 2021 Politecnico di Milano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giubots
 */

#ifndef BLV_LOG_LEVELS
#define BLV_LOG_LEVELS

// The following are the predefined log levels.
#define BLV_DEBUG_L "DEBUG"
#define BLV_INFO_L "INFO"
#define BLV_NOTICE_L "NOTICE"
#define BLV_WARN_L "WARN"
#define BLV_ERROR_L "ERROR"
#define BLV_CRIT_L "CRIT"
#define BLV_ALERT_L "ALERT"
#define BLV_FATAL_L "FATAL"

// An ordered list of the log levels that are always in the dropdown menu.
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

/// A class that parses a file and stores its entries, levels and modules.
class Parser {
private:
    QVector<LogEntry> entries;
    QVector<QString> levelLabels;
    QSet<QString> moduleLabels;

public:
    Parser();

    /// Returns the entries found in the file during parse().
    const QVector<LogEntry> &getEntries() const;

    /// Returns the default levels and those found in the file during parse().
    const QVector<QString> &getLevelLables() const;

    /// Returns the modules found in the file during parse().
    const QSet<QString> &getModuleLables() const;

    /// Scans the contents of the stream and stores the information.
    bool parse(QTextStream &logContents);
};

#endif // CONTROLLER_H
