#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>
#include <QDebug>
#include "myworker.h"
#include "animation.h"



#include <QCoreApplication>
int main(int argc, char **argv)
{
    QCoreApplication app(argc, argv);

//        QThread thread;
//        MyWorker* worker = new MyWorker();

//        worker->moveToThread(&thread);

//        QObject::connect(&thread, &QThread::started, worker, &MyWorker::doWork);
//        QObject::connect(worker, &MyWorker::finished, worker, &QObject::deleteLater);
//        QObject::connect(worker, &QObject::destroyed, &thread, &QThread::quit);
//        QObject::connect(&thread, &QThread::finished, &app, &QCoreApplication::quit);

//        thread.start();
//        qDebug() << "main: " << QThread::currentThreadId();

//        // To saved defining more signals, I'll just use invoke() here.
//        // Normally, we connect some "driver" object's signals to the
//        // pause/resume/cancel slots.
//        auto const m = worker->metaObject();

//        QThread::sleep(1);
//        m->invokeMethod(worker, "pause");
////        worker->pause();
//        QThread::sleep(4);
//        m->invokeMethod(worker, "resume");
////        worker->resume();
//        QThread::sleep(1);
//        m->invokeMethod(worker, "cancel");
////        worker->cancel();



        Animation* anim = new Animation("Animation1", 0, 100, 100, 5000);
        auto const m = anim->metaObject();

        m->invokeMethod(anim, "start", Qt::QueuedConnection);

        QThread::sleep(2);
        m->invokeMethod(anim, "pause", Qt::QueuedConnection);

        QThread::sleep(2);
        m->invokeMethod(anim, "resume", Qt::QueuedConnection);

        QThread::sleep(4);
        m->invokeMethod(anim, "cancel", Qt::QueuedConnection);


        app.exec();
}
