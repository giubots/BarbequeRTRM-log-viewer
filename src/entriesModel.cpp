#include <headers/entriesModel.h>
#include <headers/parser.h>

#include <QColor>


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
    switch (role) {
    case Qt::DisplayRole: {
        const auto &entry = entries[index.row()];
        switch (index.column()) {
        case 0: return entry.dateTime.toString("yyyy-MM-dd hh:mm:ss,zzz");
        case 1: return entry.level;
        case 2: return entry.module;
        case 3: return entry.text;
        default: return QVariant();
        }
    }
    case Qt::ForegroundRole: {
        const auto &entry = entries[index.row()];
        if (entry.level == BLV_INFO_L) return QColor(17, 209, 22); //Green
        if (entry.level == BLV_NOTICE_L) return QColor(26, 188, 156); //Cyan
        if (entry.level == BLV_WARN_L) return QColor(253, 188, 75); //Yellow
        if (entry.level == BLV_ERROR_L) return QColor(155, 89, 182); //Purple
        if (entry.level == BLV_CRIT_L) return QColor(155, 89, 182); //Purple
        if (entry.level == BLV_ALERT_L) return QColor(246, 116, 0); //Light red - orange
        if (entry.level == BLV_FATAL_L) return QColor(192, 57, 43); //Red
        return QColor(Qt::white);
    }
    case Qt::BackgroundRole: return QColor(35, 38, 39);
    default: return QVariant();
    }
}

QVariant EntriesModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return tr("Date");
        case 1: return tr("Level");
        case 2: return tr("Module");
        case 3: return tr("message");
        default: break;
        }
    }
    return QVariant();
}

const QVector<LogEntry> &EntriesModel::getEntries() const {
    return entries;
}
