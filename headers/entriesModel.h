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

#ifndef ENTRIESMODEL_H
#define ENTRIESMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

/// A LogEntry represents a line of the log file.
struct LogEntry {
    /// How the date is displayed.
    static const QString DATE_FORMAT;

    /// The timestamp of this entry.
    const QDateTime dateTime;

    /// The log level of this entry, for example DEBUG.
    const QString level;

    /// The module that emitted this log entry.
    const QString module;

    /// The message of this log entry.
    const QString message;

    /// Creates a new LogEntry with the provided parametes.
    LogEntry(QDateTime &dateTime, QString &level, QString &module, QString &message);

    LogEntry(const LogEntry &other);

    QString toString() const;
    bool operator==(const LogEntry &other) const;
    LogEntry &operator=(const LogEntry &other);
};

inline QDataStream &operator<<(QDataStream &stream, const LogEntry &entry);

/// A model for a QTable that contains some log entries.
class EntriesModel : public QAbstractTableModel {
    Q_OBJECT

private:
    QVector<LogEntry> entries;

public:
    EntriesModel(QObject *parent = nullptr);

    /// Creates a new EntriesModel with the provided entries.
    EntriesModel(const QVector<LogEntry> &entries, QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    /// Returns all the log entries contained in this model.
    const QVector<LogEntry> &getEntries() const;

    /// Adds the provided log entries to those already in this model.
    void appendData(const LogEntry &value);

    /// Removes all log entries from this model.
    void clear();
};

#endif // ENTRIESMODEL_H
