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
    QList<LogEntry> entries = contr.getFiltered();
    ui->tableWidget->setColumnCount(4);
    ui->tableWidget->setRowCount(entries.size());
    for (int i=0; i<entries.size(); i++) {
        auto entry = entries.at(i);
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(entry.dateTime.toString(Qt::DateFormat::ISODateWithMs)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(entry.level.getName()));
        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(entry.module));
        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(entry.text));
    }
}

void MainWindow::updateTable(Filter filter) {
    for( int i = 0; i < ui->tableWidget->rowCount(); ++i ) {
        bool keep = true;

        auto dateTime = QDateTime::fromString(ui->tableWidget->item(i, 0)->text(), Qt::DateFormat::ISODateWithMs);
        auto level = LogLevel::fromString(ui->tableWidget->item(i, 1)->text());
        auto module = ui->tableWidget->item(i, 2)->text();
        auto text = ui->tableWidget->item(i, 3)->text();

        if ((filter.startDateTime.isValid() && dateTime < filter.startDateTime)
                || (filter.endDateTime.isValid() && dateTime > filter.endDateTime)
                || (!filter.levels.isEmpty() && !filter.levels.contains(level))
                || (!filter.modules.isEmpty() && !filter.modules.contains(module))
                || (!filter.text.isEmpty() && !text.contains(filter.text)))
            keep = false;
        ui->tableWidget->setRowHidden(i, !keep);
    }
}

void MainWindow::on_resetButton_clicked() {
    ui->filterEdit->clear();
    updateTable(Filter());
}

void MainWindow::on_filterEdit_textEdited(const QString &text) {
    updateTable(Filter().contains(text));
}
