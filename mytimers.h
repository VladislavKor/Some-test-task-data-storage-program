#ifndef MYTIMERS_H
#define MYTIMERS_H
#include "myconstants.h"
#include <QThread>
#include <QTableWidget>
#include <cstdlib>
#include <stdint.h>

// базовый класс для обоих таймеров
class MyBaseForTimer : public QObject
{
    Q_OBJECT
private:
    static bool flag; // флаг для синхронизации добавления и умножения значений
    static QVector<QPair<uint32_t, uint32_t>> vec; // для хранения сгенерированных чисел
    QVector<QPair<QString, QString>> &tableRows; // ссылка на вектор хранящий строковые представления чисел
public:
    // констуркутор
    MyBaseForTimer(QVector<QPair<QString, QString>>& tableRows) : tableRows(tableRows){}
    // Функция генерирует и добавляет новое число и его строковое представление
    // в соответсвующие вектора, если в данный момент выполняется умножение значения,
    // то функция ничего не делает
    void addNewValue()
    {
        static int i = 0;
        if (!flag)
        {
            if (i == SIZE)
                i = 0;

            vec[i].first = (uint32_t)rand();
            vec[i].second = 0;
            tableRows[i].first = QString::number(vec[i].first);
            tableRows[i].second = QString("");
            i++;
            emit mySignal(); // отправляем сигнал для обновления tableView
        }
    }
    // функция извлекает число и вектора чисел, производит умножение,
    // помещает результат умножения и строковое представление результата в соответсвующие вектора
    void multiplyValue()
    {
        static int i = 0;
        flag = true;
        if (i == SIZE)
            i = 0;

        vec[i].second = vec[i].first * 2;
        tableRows[i].second = QString::number(vec[i].second);
        i++;
        flag = false;
        emit mySignal(); // отправляем сигнал для обновления tableView
    }
signals:
    void mySignal();
};


class Timer1 : public MyBaseForTimer, public QThread
{
public:
    // конструктор
    Timer1(QVector<QPair<QString, QString>>& tableRows) : MyBaseForTimer(tableRows){}
    void run()
    {
        while (1)
        {
            msleep(minDelay + rand() % (maxDelay - minDelay)); // таймер ожидает некоторое время
            addNewValue(); // вызываем функцию генерации нового значения
        }
    }
};

class Timer2 : public MyBaseForTimer, public QThread
{
public:
    Timer2(QVector<QPair<QString, QString>>& tableRows) : MyBaseForTimer(tableRows){}
    void run()
    {
        while (1)
        {
            msleep(delay);
            multiplyValue(); // вызов функции умножения числа
        }
    }
};

#endif // MYTIMERS_H
