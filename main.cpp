#include "mainwindow.h"
#include <QApplication>
#include <QObject>
#include "mytimers.h"

bool MyBaseForTimer::flag = false;
QVector<QPair<uint32_t, uint32_t>> MyBaseForTimer::vec = QVector<QPair<uint32_t, uint32_t>>(SIZE, QPair<uint32_t, uint32_t>(0,0));

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    QVector<QPair<QString, QString>> tableRows(SIZE, QPair<QString, QString>("", ""));

    srand(time(0)); // посев генератора случайных чисел

    Timer1 timer1(tableRows);
    Timer2 timer2(tableRows);
    w.setModelForTableView(tableRows); // привязываем tableView к данным вектора tableRows

    QObject::connect(&static_cast<MyBaseForTimer&>(timer1), SIGNAL(mySignal()), &w, SLOT(updateTableView()));
    QObject::connect(&static_cast<MyBaseForTimer&>(timer2), SIGNAL(mySignal()), &w, SLOT(updateTableView()));

    timer1.start();
    timer2.start();

    w.show();

    return a.exec();
}
