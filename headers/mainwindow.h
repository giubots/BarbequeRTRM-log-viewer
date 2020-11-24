#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "entriesModel.h"
#include "filter.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    EntriesModel *entriesModel;
    Filter *filter;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private:
    void updateTable();
private slots:
    void on_openButton_clicked();//TODO (&seq) change to programmatic? connect?
    //void on_resetButton_clicked();//TODO (&seq) change to programmatic? connect?
    //void on_filterEdit_textEdited(const QString &text);//TODO (&seq) change to programmatic? connect?
    //void slot_changed(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};
#endif // MAINWINDOW_H
