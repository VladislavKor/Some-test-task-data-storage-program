#include "mainwindow.h"
#include "ui_mainwindow.h"

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

void MainWindow::setModelForTableView(QVector<QPair<QString, QString>> &tableRows)
{
    model = new MyTableModel(tableRows);
    ui->tableView->setModel(model);
}

void MainWindow::updateTableView()
{
    ui->tableView->reset();
}
