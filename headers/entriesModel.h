#ifndef ENTRIESMODEL_H
#define ENTRIESMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

struct LogEntry {
    const QDateTime dateTime;
    const QString level;
    const QString module;
    const QString text;

    QString toString() const;
    bool operator==(const LogEntry &other) const;
};

inline QDataStream &operator<<(QDataStream &stream, const LogEntry &entry);

class EntriesModel : public QAbstractTableModel {
    Q_OBJECT
private:
    QVector<LogEntry> entries;
public:
    EntriesModel(QObject *parent = nullptr);
    EntriesModel(const QVector<LogEntry> &entries, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent) const override;
    int columnCount(const QModelIndex &parent) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    const QVector<LogEntry> &getEntries() const;
};

#endif // ENTRIESMODEL_H
