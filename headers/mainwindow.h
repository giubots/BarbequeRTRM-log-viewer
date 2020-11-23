#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_filterEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Controller contr;
private:
    void updateTable(QList<LogEntry> entries);
};
#endif // MAINWINDOW_H
