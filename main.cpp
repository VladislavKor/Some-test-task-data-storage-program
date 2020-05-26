#include "mainwindow.h"
#include "mytimers.h"
#include <QApplication>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    MyTimerOne timer1(300, 600);
    MyTimerTwo timer2(1000);

    QObject::connect(&timer1, SIGNAL(newValue(quint32)), &w, SLOT(addValue(quint32)));
    QObject::connect(&timer2, SIGNAL(multiply()), &w, SLOT(multiplyValue()));

    w.show();
    timer1.start();
    timer2.start();

    return a.exec();
}
