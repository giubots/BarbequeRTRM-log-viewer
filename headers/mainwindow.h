#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "entriesModel.h"
#include "filter.h"

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QStandardItemModel *levelModel;
    QStandardItemModel *moduleModel;
    EntriesModel *entriesModel;
    Filter *filter;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void updateTable();

private slots:
    void onOpen();
    void onReset();
    void onFilterText(const QString &text);
    void onToggleDate(int state);
    void onSinceEdit(const QString &text);
    void onUntilEdit(const QString &text);
    void onLevelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
    void onModuleChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};
#endif // MAINWINDOW_H
