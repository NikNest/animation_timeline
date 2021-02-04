#ifndef ANIMATION_H
#define ANIMATION_H
#include <QString>
#include <QObject>
#include <QThread>
#include <QWaitCondition>
#include <QCoreApplication>
#include <QTime>
#include <QAbstractEventDispatcher>
#include <QObject>
#include <QThread>
#include <QDebug>
#include "gui.h"

class Animation : public QObject {
    Q_OBJECT

    enum State { IDLE, RUNNING, PAUSED };

    Gui* gui;
    QString name;
    double startValue;
    double endValue;
    double currentValue;
    unsigned delay;
    unsigned duration;
    unsigned time;
    State state;
    QThread* animationRunner;

public:
    explicit Animation(QString _name, double _startVal, double _endVal, unsigned _delay, unsigned _duration, QObject *parent = 0) :
        QObject(parent), name(_name), startValue(_startVal), endValue(_endVal), currentValue(_startVal), delay(_delay), duration(_duration), time(0),
        state(IDLE) {
        animationRunner = new QThread();
        gui = new Gui();
        this->moveToThread(animationRunner);
        gui->moveToThread(animationRunner);

        QObject::connect(this, &Animation::showTimeGUI, gui, &Gui::printTime);
        QObject::connect(this, &Animation::showValueGUI, gui, &Gui::printValue);
        QObject::connect(this, &Animation::resumePressed, gui, &Gui::printResume);
        QObject::connect(this, &Animation::cancelPressed, gui, &Gui::printCancel);
        QObject::connect(this, &Animation::restartPressed, gui, &Gui::printRestart);
        QObject::connect(this, &Animation::finish, gui, &Gui::printFinish);
        QObject::connect(this, &Animation::pausePressed, gui, &Gui::printPause);
        QObject::connect(this, &Animation::startPressed, gui, &Gui::printStart);


//        TODO: так работало в примере, адаптировать
//        QObject::connect(animationRunner, &QThread::started, this, &Animation::doWork);

        QObject::connect(this, &QObject::destroyed, animationRunner, &QThread::quit);

        animationRunner->start();
    }
    void doWork();

public slots:
    void resume();
    void pause();
    void cancel();
    void restart();
    void start();

private:



    bool isCancelled() {
        auto const dispatcher = QThread::currentThread()->eventDispatcher();
        if (!dispatcher) {
            qCritical() << "thread with no dispatcher";
            return false;
        }
        dispatcher->processEvents(QEventLoop::AllEvents);
        return state == IDLE;
    }

signals:
    //for connection with GUI
    void showTimeGUI(unsigned _currentTime);
    void showValueGUI(double _currentValue);
    void resumePressed();
    void restartPressed();
    void pausePressed();
    void cancelPressed();
    void finish();
    void startPressed();
};

#endif // ANIMATION_H
