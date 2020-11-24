#include <headers/entriesModel.h>


QString LogEntry::toString() const {
    return dateTime.toString(Qt::ISODateWithMs) + " " + level + " - " + module + " : " + text;
}

bool LogEntry::operator==(const LogEntry &other) const {
    return dateTime == other.dateTime && level == other.level && module == other.module && text == other.text;
}

QDataStream &operator<<(QDataStream &stream, const LogEntry &entry) {
    return stream << entry.dateTime << entry.level << entry.module << entry.text;
}

EntriesModel::EntriesModel(QObject *parent)
    : QAbstractTableModel(parent) {}

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
    if (!index.isValid()) return QVariant();
    if (index.row() >= entries.size() || index.row() < 0) return QVariant();
    if (role == Qt::DisplayRole) {
        const auto &entry = entries[index.row()];
        switch (index.column()) {
        case 0: return entry.dateTime.toString(Qt::DateFormat::ISODateWithMs);
        case 1: return entry.level;
        case 2: return entry.module;
        case 3: return entry.text;
        default: break;
        }
    }
    return QVariant();
}
