#ifndef WORKER_H
#define WORKER_H
#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>
#include <QDebug>


class Worker : public QObject
{
    Q_OBJECT

public:
    explicit Worker(QObject *parent = 0)
        : QObject(parent) {}

signals:
    void started();
    void finished();

public slots:
    void pause()
    {
        auto const dispatcher = QThread::currentThread()->eventDispatcher();
        if (!dispatcher) {
            qCritical() << "thread with no dispatcher";
            return;
        }

        if (state != RUNNING)
            return;

        state = PAUSED;
        qDebug() << "pause: " << QThread::currentThreadId();

        qDebug() << "paused";
        do {
            dispatcher->processEvents(QEventLoop::WaitForMoreEvents);
        } while (state == PAUSED);
    }

    void resume()
    {
        if (state == PAUSED) {
            state = RUNNING;
            qDebug() << "resume: " << QThread::currentThreadId();

            qDebug() << "resumed";
        }
    }

    void cancel() {
        if (state != IDLE) {
            state = IDLE;
            qDebug() << "cancel: " << QThread::currentThreadId();

            qDebug() << "cancelled";
        }
    }

protected:

    enum State { IDLE, RUNNING, PAUSED };
    State state = IDLE;

    bool isCancelled() {
        qDebug() << "is canceled: " << QThread::currentThreadId();

        auto const dispatcher = QThread::currentThread()->eventDispatcher();
        if (!dispatcher) {
            qCritical() << "thread with no dispatcher";
            return false;
        }
        dispatcher->processEvents(QEventLoop::AllEvents);
        return state == IDLE;
    }

};

#endif // WORKER_H
