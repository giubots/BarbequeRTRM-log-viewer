#include "headers/mainwindow.h"
#include "ui_mainwindow.h"

#include <headers/controller.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_openButton_clicked()
{
    //QString fileName = QFileDialog::getOpenFileName(this);
}
