#ifndef FILTER_H
#define FILTER_H

#include "entriesModel.h"

#include <QSet>

class Filter {
private:
    QDateTime since;
    QDateTime until;
    QSet<QString> levelsBlacklist;
    QSet<QString> modulesBlacklist;
    QString contains;
public:
    Filter &setSince(const QDateTime &since);
    Filter &removeSince();
    Filter &setUntil(const QDateTime &until);
    Filter &removeUntil();
    Filter &hideLevel(const QString &level);
    Filter &showLevel(const QString &level);
    Filter &hideModule(const QString &module);
    Filter &showModule(const QString &module);
    Filter &setContains(const QString &contains);
    Filter &removeContains();
    Filter &clear();
    bool toHide(const LogEntry &entry) const;
};

#endif // FILTER_H
