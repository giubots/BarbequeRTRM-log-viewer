/*
 * Copyright (C) 2021 Politecnico di Milano
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Author: Giubots
 */

#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <headers/parser.h>

#include <QFile>
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , levelModel(new QStandardItemModel)
    , moduleModel(new QStandardItemModel)
    , entriesModel(new EntriesModel(this))
    , filter(new Filter()) {

    // Initializes the user interface.
    ui->setupUi(this);

    // The date filter toolbar is initially hidden.
    ui->horizontalWidget->setVisible(false);

    // Sets the model for the initially empty table.
    ui->tableView->setModel(entriesModel);

    // Comment the next line to allow the user to manually resize the columns.
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::ResizeToContents);
}

MainWindow::~MainWindow() {
    delete ui;
    delete levelModel;
    delete moduleModel;
    delete entriesModel;
    delete filter;
}

void MainWindow::updateTable() {
    auto entries = entriesModel->getEntries();
    for(int i = 0; i < entries.size(); ++i)
        ui->tableView->setRowHidden(i, filter->toHide(entries[i]));
}


void MainWindow::onOpen() {
    // Show a dialog to choose a file.
    QString fileName = QFileDialog::getOpenFileName(this);

    // Try to open the file and parse its contents.
    if (!fileName.isEmpty()) {
        QFile inputFile(fileName);
        if (inputFile.open(QIODevice::ReadOnly)) {
            QTextStream in(&inputFile);
            Parser parser;
            auto success = parser.parse(in);

            if (!success) {
                QMessageBox msgBox;
                msgBox.setText("Some entries could not be parsed.");
                msgBox.exec();
            }

            // Remove previous filters.
            ui->filterEdit->clear();
            ui->sinceEdit->clear();
            ui->untilEdit->clear();
            filter->clear();

            // Set the new entries model.
            delete entriesModel;
            entriesModel = new EntriesModel(parser.getEntries(), this);
            ui->tableView->setModel(entriesModel);
            updateTable();

            // Set the new levels in the dropdown menu.
            delete levelModel;
            auto levels = parser.getLevelLables();
            levelModel = new QStandardItemModel(levels.size()+1, 1);
            levelModel->setItem(0, 0, new QStandardItem(tr("Level: ")));
            for (int i = 0; i < levels.size(); ++i) {
                auto item = new QStandardItem();
                item->setText(levels[i]);
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setData(Qt::Checked, Qt::CheckStateRole);
                levelModel ->setItem(i+1, 0, item);
            }

            // Connect the new level model to the corresponding method.
            connect(levelModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
                    this, SLOT(onLevelChanged(const QModelIndex&, const QModelIndex&)));
            ui->levelDropdown->setModel(levelModel);

            // Set the modules in the dropdown menu, alphabetically sorted.
            delete moduleModel;
            auto modules = parser.getModuleLables().values();
            std::sort(modules.begin(), modules.end());
            moduleModel = new QStandardItemModel(modules.size()+1, 1);
            moduleModel ->setItem(0, 0, new QStandardItem(tr("Module: ")));
            for (int i = 0; i < modules.size(); ++i) {
                auto item = new QStandardItem();
                item->setText(modules[i]);
                item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
                item->setData(Qt::Checked, Qt::CheckStateRole);
                moduleModel ->setItem(i+1, 0, item);
            }

            // Connect the new module model to the corresponding method.
            connect(moduleModel, SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)),
                    this, SLOT(onModuleChanged(const QModelIndex&, const QModelIndex&)));
            ui->moduleDropdown->setModel(moduleModel);

        } else {
            qDebug() << "Impossible to open: " << fileName;
            QMessageBox msgBox;
            msgBox.setText("Impossible to open the file.");
            msgBox.exec();
        }
        inputFile.close();
    }
}

void MainWindow::onReset() {
    ui->filterEdit->clear();
    ui->sinceEdit->clear();
    ui->untilEdit->clear();
    for(int i = 1; i < levelModel->rowCount(); ++i) levelModel->item(i)->setData(Qt::Checked, Qt::CheckStateRole);
    for(int i = 1; i < moduleModel->rowCount(); ++i) moduleModel->item(i)->setData(Qt::Checked, Qt::CheckStateRole);
    filter->clear();
    updateTable();
}

void MainWindow::onFilterText(const QString &text) {
    filter->setContains(text);
    updateTable();
}


void MainWindow::onToggleDate(int state) {
    switch (state) {
    case Qt::Unchecked:
        filter->removeSince();
        filter->removeUntil();
        ui->sinceEdit->clear();
        ui->untilEdit->clear();
        ui->horizontalWidget->setVisible(false);
        break;
    case Qt::Checked:
        ui->horizontalWidget->setVisible(true);
        break;
    default:
        break;
    }
    updateTable();
}

void MainWindow::onSinceEdit(const QString &text) {
    filter->setSince(QDateTime::fromString(text, Qt::DateFormat::ISODateWithMs));
    updateTable();
}

void MainWindow::onUntilEdit(const QString &text) {
    filter->setUntil(QDateTime::fromString(text, Qt::DateFormat::ISODateWithMs));
    updateTable();
}

void MainWindow::onLevelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
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

void MainWindow::onModuleChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
    Q_UNUSED(bottomRight);
    QStandardItem* item = moduleModel->item(topLeft.row());
    switch (item->checkState()) {
    case Qt::Unchecked:
        filter->hideModule(item->text());
        break;
    case Qt::Checked:
        filter->showModule(item->text());
        break;
    default:
        break;
    }
    updateTable();
}

