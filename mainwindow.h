#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <stdint.h>
#include <QTableWidget>

#include "myconstants.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// модель представления данных для оторбражения в tableView
class MyTableModel : public QAbstractTableModel
{
public:
    MyTableModel(QVector<QPair<QString, QString>> &tableRows) : tableRows(tableRows){}
private:
    int rowCount(const QModelIndex &parent) const Q_DECL_OVERRIDE { Q_UNUSED(parent); return SIZE;}
    int columnCount(const QModelIndex &parent) const Q_DECL_OVERRIDE {Q_UNUSED(parent); return 2;}
    QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE
    {
        if (role == Qt::DisplayRole && index.isValid())
        {
            if (index.column() == 0)
                return tableRows[index.row()].first;
            if (index.column() == 1)
                return tableRows[index.row()].second;
        }
        return QVariant();
    }
    QVariant headerData(int section, Qt::Orientation orientation, int role) const Q_DECL_OVERRIDE
    {
        if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
        {
            if (section == 0)
                return QString("Исходное занчение");
            if (section == 1)
                return QString("Результат");
        }
        return QVariant();
    }

    QVector<QPair<QString, QString>> &tableRows;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    // функция устанавливает модель для tableView на основе данных вектора tableRows
    void setModelForTableView(QVector<QPair<QString, QString>> &tableRows);
public slots:
    // обновляет tableView по сигналу mySignal от timer1 и timer2
    void updateTableView();
private:
    Ui::MainWindow *ui;
    MyTableModel* model;
};
#endif // MAINWINDOW_H
