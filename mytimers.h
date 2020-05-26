#ifndef MYTIMERS_H
#define MYTIMERS_H

#include <QThread>
#include <cstdlib>
#include <stdint.h>

class MyTimerOne : public QThread
{
    Q_OBJECT
public:
    MyTimerOne(int min, int max)
    {
        minDelay = min;
        maxDelay = max;
    }
    void run()
    {
        while (1)
        {
            msleep(minDelay + rand() % (maxDelay - minDelay));
            emit newValue(rand());
        }
    }
signals:
    void newValue(quint32);
private:
    int minDelay;
    int maxDelay;
};

class MyTimerTwo : public QThread
{
    Q_OBJECT
public:
    MyTimerTwo(int _delay)
    {
        delay = _delay;
    }
    void run()
    {
        while (1)
        {
            msleep(delay);
            emit multiply();
        }
    }
signals:
    void multiply();
private:
    int delay;
};

#endif // MYTIMERS_H
