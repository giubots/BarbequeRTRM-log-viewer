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

#ifndef FILTER_H
#define FILTER_H


#include "entriesModel.h"

#include <QDateTime>
#include <QSet>

/**
 * A class that represents a filter on the log entries.
 * Filter fields are added to each other: an entry is hidden if does not satisfies one or more filters.
 * The methods of this class return the updated instance they where called on.
 */
class Filter {
private:
    QDateTime since;
    QDateTime until;
    QSet<QString> levelsBlacklist;
    QSet<QString> modulesBlacklist;
    QString contains;

public:
    /// Hides all the entries before and not equal to this timestamp.
    Filter &setSince(const QDateTime &since);

    /// Removes the filter set with setSince().
    Filter &removeSince();

    /// Hides all the entries after and not equal to this timestamp.
    Filter &setUntil(const QDateTime &until);

    /// Removes the filter set with setUntil().
    Filter &removeUntil();

    /// Hides all entries with this level, does not overwrite previous filters.
    Filter &hideLevel(const QString &level);

    /// Removes the filter on this level, but leaves the others.
    Filter &showLevel(const QString &level);

    /// Hides all entries with this module, does not overwrite previous filters.
    Filter &hideModule(const QString &module);

    /// Removes the filter on this module, but leaves the others.
    Filter &showModule(const QString &module);

    /// Hides all entries that do not contain this string in the message.
    Filter &setContains(const QString &contains);

    /// Removes the filter on the message contents.
    Filter &removeContains();

    /// Removes all filters.
    Filter &clear();

    /// Determines whether a log entry is filtered out by this filter.
    bool toHide(const LogEntry &entry) const;
};

#endif // FILTER_H
