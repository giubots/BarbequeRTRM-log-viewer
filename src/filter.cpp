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

#include <headers/filter.h>

Filter &Filter::setSince(const QDateTime &since) {
    this->since = since;
    return *this;
}

Filter &Filter::removeSince() {
    since = QDateTime();
    return *this;
}

Filter &Filter::setUntil(const QDateTime &until) {
    this->until = until;
    return *this;
}

Filter &Filter::removeUntil() {
    until = QDateTime();
    return *this;
}

Filter &Filter::hideLevel(const QString &level) {
    levelsBlacklist << level;
    return *this;
}

Filter &Filter::showLevel(const QString &level) {
    levelsBlacklist -= level;
    return *this;
}

Filter &Filter::hideModule(const QString &module) {
    modulesBlacklist << module;
    return *this;
}

Filter &Filter::showModule(const QString &module) {
    modulesBlacklist -= module;
    return *this;
}

Filter &Filter::setContains(const QString &contains) {
    this->contains = contains;
    return *this;
}

Filter &Filter::removeContains() {
    contains = "";
    return  *this;
}

Filter &Filter::clear() {
    removeSince();
    removeUntil();
    levelsBlacklist.clear();
    modulesBlacklist.clear();
    removeContains();
    return *this;
}

bool Filter::toHide(const LogEntry &entry) const {
    return ((since.isValid() && entry.dateTime < since)
            || (until.isValid() && entry.dateTime > until)
            || levelsBlacklist.contains(entry.level)
            || modulesBlacklist.contains(entry.module)
            || !entry.message.contains(contains));
}
