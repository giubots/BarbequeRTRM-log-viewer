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
    since = QDateTime();
    until = QDateTime();
    levelsBlacklist.clear();
    modulesBlacklist.clear();
    contains = "";
    return *this;
}

bool Filter::toHide(const LogEntry &entry) const {
    return ((since.isValid() && entry.dateTime < since)
            || (until.isValid() && entry.dateTime > until)
            || levelsBlacklist.contains(entry.level)
            || modulesBlacklist.contains(entry.module)
            || !entry.text.contains(contains));
}
