#ifndef ENTRIESMODEL_H
#define ENTRIESMODEL_H

#include <QAbstractTableModel>
#include <QDateTime>

struct LogEntry {
    static const QString DATE_FORMAT;

    const QDateTime dateTime;
    const QString level;
    const QString module;
    const QString message;

    LogEntry(QDateTime &dateTime, QString &level, QString &module, QString &message);
    LogEntry(const LogEntry &other);

    QString toString() const;
    bool operator==(const LogEntry &other) const;
    LogEntry &operator=(const LogEntry &other);
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
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    const QVector<LogEntry> &getEntries() const;
    void appendData(const LogEntry &value);
    void clear();
};

#endif // ENTRIESMODEL_H
