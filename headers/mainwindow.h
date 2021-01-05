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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "entriesModel.h"
#include "filter.h"

#include <QMainWindow>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

/// The main window, holds various models and handles the interaction with the UI.
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
    /// Opens a new file in this window.
    void onOpen();

    /// Removes all filters.
    void onReset();

    /// Adds a filter on the message.
    void onFilterText(const QString &text);

    /// Toggles whether the toolbar with the date filters is enabled.
    void onToggleDate(int state);

    /// Adds a since filter on the date.
    void onSinceEdit(const QString &text);

    /// Adds an until filter on the date.
    void onUntilEdit(const QString &text);

    /// Called when the level dropdown menu selection changes, modifies the level filters.
    void onLevelChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);

    /// Called when the module dropdown menu selection changes, modifies the module filters.
    void onModuleChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight);
};
#endif // MAINWINDOW_H
