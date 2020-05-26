#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Исходное значение"));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Результат"));

    flag = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addValue(quint32 value)
{
    static int i = 1;
    if (i > 100)
        i = 1;
    if (!flag)
    {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(value)));
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(""));
        i++;
    }
}

void MainWindow::multiplyValue()
{
    static int i = 1;
    flag = true;
    quint32 val;
    if (i > 100)
        i = 1;

    QTableWidgetItem *a = ui->tableWidget->item(i,0);
    if (a)
    {
        val = a->text().toUInt();
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem(QString::number(val * 2)));
        i++;
    }
    flag = false;
}
