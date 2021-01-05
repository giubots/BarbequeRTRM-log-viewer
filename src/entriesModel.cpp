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

#include <headers/entriesModel.h>
#include <headers/parser.h>

#include <QColor>

// Change this value to modify how the timestams are displayed in the application.
const QString LogEntry::DATE_FORMAT = "yyyy-MM-dd hh:mm:ss,zzz";

LogEntry::LogEntry(QDateTime &dateTime, QString &level, QString &module, QString &message)
    : dateTime(dateTime)
    , level(level)
    , module(module)
    , message(message) {}

LogEntry::LogEntry(const LogEntry &other)
    : dateTime(other.dateTime)
    , level(other.level)
    , module(other.module)
    , message(other.message) {}

QString LogEntry::toString() const {
    return dateTime.toString(DATE_FORMAT) + " - " + level + " " + module + " : " + message;
}

bool LogEntry::operator==(const LogEntry &other) const {
    return dateTime == other.dateTime && level == other.level && module == other.module && message == other.message;
}

LogEntry &LogEntry::operator=(const LogEntry &other) {
    LogEntry temp(other);
    std::swap(*this, temp);
    return *this;
}

QDataStream &operator<<(QDataStream &stream, const LogEntry &entry) {
    return stream << entry.toString();
}

EntriesModel::EntriesModel(QObject *parent)
    : QAbstractTableModel(parent)
    , entries() {}

EntriesModel::EntriesModel(const QVector<LogEntry> &entries, QObject *parent)
    : QAbstractTableModel(parent)
    , entries(entries) {}

int EntriesModel::rowCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : entries.size();
}

int EntriesModel::columnCount(const QModelIndex &parent) const {
    return parent.isValid() ? 0 : 4;
}

QVariant EntriesModel::data(const QModelIndex &index, int role) const {
    // Handle not valid index.
    if (!index.isValid()) return QVariant();
    if (index.row() >= entries.size() || index.row() < 0) return QVariant();

    switch (role) {
    case Qt::DisplayRole: {
        // Return the contents of the various cells.
        const auto &entry = entries[index.row()];
        switch (index.column()) {
        case 0: return entry.dateTime.toString(LogEntry::DATE_FORMAT);
        case 1: return entry.level;
        case 2: return entry.module;
        case 3: return entry.message;
        default: return QVariant();
        }
    }
    case Qt::ForegroundRole: {
        // Return the text color.
        const auto &entry = entries[index.row()];
        if (entry.level == BLV_INFO_L)      return QColor(17, 209, 22);     //Green
        if (entry.level == BLV_NOTICE_L)    return QColor(26, 188, 156);    //Cyan
        if (entry.level == BLV_WARN_L)      return QColor(253, 188, 75);    //Yellow
        if (entry.level == BLV_ERROR_L)     return QColor(155, 89, 182);    //Purple
        if (entry.level == BLV_CRIT_L)      return QColor(155, 89, 182);    //Purple
        if (entry.level == BLV_ALERT_L)     return QColor(246, 116, 0);     //Light red - orange
        if (entry.level == BLV_FATAL_L)     return QColor(192, 57, 43);     //Red
        return QColor(Qt::white);
    }
    default: return QVariant();
    }
}

QVariant EntriesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    // Handle invalid role.
    if (role != Qt::DisplayRole) return QVariant();

    // Return the header titles.
    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return tr("Date");
        case 1: return tr("Level");
        case 2: return tr("Module");
        case 3: return tr("Message");
        default: break;
        }
    }
    return QVariant();
}

const QVector<LogEntry> &EntriesModel::getEntries() const {
    return entries;
}

void EntriesModel::appendData(const LogEntry &value) {
    beginInsertRows(QModelIndex(), entries.size()+1, entries.size()+1);
    entries.append(value);
    endInsertRows();
}

void EntriesModel::clear() {
    beginResetModel();
    entries.clear();
    endResetModel();
}


