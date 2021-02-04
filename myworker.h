#ifndef MYWORKER_H
#define MYWORKER_H
#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>
#include <QDebug>
#include "worker.h"


class MyWorker : public Worker
{
    Q_OBJECT

public:
    explicit MyWorker(QObject *parent = 0)
        : Worker(parent)
    {
    }
public slots:
    void doWork()
    {

        if (state == PAUSED) {
            // treat as resume
            state = RUNNING;
        }

        if (state == RUNNING) {
            qDebug() << "hi";
            return;
        }

        state = RUNNING;
        qDebug() << "started";
        emit started();

        // This loop simulates the actual work
        for (auto i = 0u;  state == RUNNING;  ++i) {
            QThread::msleep(100);
            if (isCancelled()) break;
            qDebug() << i;
        }

        qDebug() << "finished";
        emit finished();
    }
};

#endif // MYWORKER_H
