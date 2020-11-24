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

//inline QDataStream &operator>>(QDataStream &stream, LogEntry &entry); //TODO: remove

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
    //QVariant headerData(int section, Qt::Orientation orientation, int role) const override;//TODO: remove
    //Qt::ItemFlags flags(const QModelIndex &index) const override; //TODO: remove
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override; //TODO: remove
    //bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override; //TODO: remove
    //bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override; //TODO: remove
    //const QVector<LogEntry> &getEntries() const; //TODO: remove
};

#endif // ENTRIESMODEL_H
