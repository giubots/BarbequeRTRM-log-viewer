#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <headers/parser.h>

#include <QFile>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , levelModel(new QStandardItemModel)
    , entriesModel(new EntriesModel(this))
    , filter(new Filter()) {
    ui->setupUi(this);
    //TODO: make hardcoded?
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

MainWindow::~MainWindow() {
    delete ui;
    delete levelModel;
    delete entriesModel;
    delete filter;
}

void MainWindow::updateTable() {
    auto entries = entriesModel->getEntries();
    for(int i = 0; i < entries.size(); ++i)
        ui->tableView->setRowHidden(i, filter->toHide(entries[i]));
}


void MainWindow::on_openButton_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this);
    //QString fileName = "/home/giubots/Desktop/bbque.log";
    if (!fileName.isEmpty()) {
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);
            auto parser = Parser(in);

            filter->clear();
            ui->filterEdit->clear();

            delete entriesModel;
            entriesModel = new EntriesModel(parser.getEntries(), this);
            ui->tableView->setModel(entriesModel);
            updateTable();

            delete levelModel;
            auto levels = parser.getLevelLables().values();
            levelModel = new QStandardItemModel(levels.size()+1, 1);
            levelModel ->setItem(0, 0, new QStandardItem(tr("Level: ")));
            for (int i = 0; i < levels.size(); ++i) {
                auto item = new QStandardItem();
                item->setText(levels[i]);
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setData(Qt::Checked, Qt::CheckStateRole);
                levelModel ->setItem(i+1, 0, item);
            }
            connect(levelModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
                    this, SLOT(levelChanged(const QModelIndex&, const QModelIndex&)));
            ui->levelDropdown->setModel(levelModel);
        } else qDebug() << "Impossible to open: " << fileName;
        inputFile.close();
    }
}

void MainWindow::on_resetButton_clicked() {
    ui->filterEdit->clear();
    for(int i = 1; i < levelModel->rowCount(); ++i) levelModel->item(i)->setData(Qt::Checked, Qt::CheckStateRole);
    filter->clear();
    updateTable();
}

void MainWindow::on_filterEdit_textEdited(const QString &text) {
    filter->setContains(text);
    updateTable();
}

void MainWindow::levelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    Q_UNUSED(bottomRight);
    QStandardItem* item = levelModel->item(topLeft.row());
    switch (item->checkState()) {
    case Qt::Unchecked:
        filter->hideLevel(item->text());
        break;
    case Qt::Checked:
        filter->showLevel(item->text());
        break;
    default:
        break;
    }
    updateTable();
}
