#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <headers/controller.h>

#include <QFile>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , contr(EmptyController()) {
    ui->setupUi(this);
    ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_openButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this);
    //QString fileName = "/home/giubots/Desktop/bbque.log";

    if (!fileName.isEmpty()) {
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);
            contr = Controller(in);
        } else qDebug() << "Impossible to open: " << fileName;
        inputFile.close();
    }

    auto entries = contr.getFiltered();

    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(entries.size());
    for (int i=0; i<entries.size(); i++) {
        auto entry = entries.at(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(entry.dateTime.toString(Qt::DateFormat::ISODateWithMs)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(entry.level.getName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(entry.module));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(entry.text));
    }
    ui->tableWidget->update();

}

void MainWindow::on_filterEdit_textChanged(const QString &arg1)
{

}
