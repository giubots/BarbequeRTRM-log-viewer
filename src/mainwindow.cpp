#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <headers/parser.h>

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMetaType>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , entriesModel(new EntriesModel(this))
    , filter(new Filter()) {
    ui->setupUi(this);
    //TODO: make hardcoded?
    ui->tableView->setModel(entriesModel);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

MainWindow::~MainWindow() {
    delete ui;
    delete entriesModel;
    delete filter;
}

//void MainWindow::updateTable() {
//    entriesModel.
//    for( int i = 0; i < ui->tableView->rowCount(); ++i ) {
//        bool keep = true;

//        auto dateTime = QDateTime::fromString(ui->tableWidget->item(i, 0)->text(), Qt::DateFormat::ISODateWithMs);
//        auto level = LogLevel::fromString(ui->tableWidget->item(i, 1)->text());
//        auto module = ui->tableWidget->item(i, 2)->text();
//        auto text = ui->tableWidget->item(i, 3)->text();

//        if ((filter.startDateTime.isValid() && dateTime < filter.startDateTime)
//                || (filter.endDateTime.isValid() && dateTime > filter.endDateTime)
//                || (!filter.levels.isEmpty() && !filter.levels.contains(level))
//                || (!filter.modules.isEmpty() && !filter.modules.contains(module))
//                || (!filter.text.isEmpty() && !text.contains(filter.text)))
//            keep = false;
//        ui->tableWidget->setRowHidden(i, !keep);
//    }
//}

//void MainWindow::updateTable() {

//}


void MainWindow::on_openButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this);
    //QString fileName = "/home/giubots/Desktop/bbque.log";
    qDebug() << "parsing ";
    if (!fileName.isEmpty()) {
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);
            auto parser = Parser(in);
            delete entriesModel;
            entriesModel = new EntriesModel(parser.getEntries(), this);
            ui->tableView->setModel(entriesModel);
        } else qDebug() << "Impossible to open: " << fileName;
        inputFile.close();
    }

//    QList<LogEntry> entries = contr.getFiltered();
//    ui->tableWidget->setColumnCount(4);
//    ui->tableWidget->setRowCount(entries.size());
//    for (int i=0; i<entries.size(); i++) {
//        auto entry = entries.at(i);
//        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(entry.dateTime.toString(Qt::DateFormat::ISODateWithMs)));
//        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(entry.level.getName()));
//        ui->tableWidget->setItem(i, 2, new QTableWidgetItem(entry.module));
//        ui->tableWidget->setItem(i, 3, new QTableWidgetItem(entry.text));
    }


//    auto levels = contr.getLevelLables();
//    auto model = new QStandardItemModel(levels.size()+1, 1);
//    model->setItem(0, 0, new QStandardItem(tr("Level: ")));

//    for (int i = 0; i < levels.size(); ++i)

//    {
//        auto item = new QStandardItem();
//        item->setText(levels.at(i));
//        item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
//        item->setData(Qt::Checked, Qt::CheckStateRole);
//        model->setItem(i+1, 0, item);
//    }

//    connect(model, SIGNAL(dataChanged ( const QModelIndex&, const QModelIndex&)), this, SLOT(slot_changed(const QModelIndex&, const QModelIndex&)));
//    ui->levelDropdown->setModel(model);
//}

//void MainWindow::on_resetButton_clicked() {
//    ui->filterEdit->clear();
//    ui->levelDropdown->setCurrentIndex(-1);
//    updateTable();
//}

//void MainWindow::on_filterEdit_textEdited(const QString &text) {
//    filter.contains(text);
//    updateTable();
//}

//void MainWindow::slot_changed(const QModelIndex& topLeft, const QModelIndex& bottomRight)
//{
//    Q_UNUSED(bottomRight);
//    QStandardItem* item = ((QStandardItemModel*) topLeft.model())->item(topLeft.row());
//    switch (item->checkState()) {
//    case Qt::Unchecked: filter = filter.removeLevel(LogLevel::fromString(item->text()));
//        break;
//    case Qt::Checked: filter = filter.addLevel(LogLevel::fromString(item->text()));
//        break;
//    default:
//        break;
//    }
//    updateTable();
//}
