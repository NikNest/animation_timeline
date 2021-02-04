#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <iostream>
#include <QDebug>

class Gui : public QObject {
Q_OBJECT
public slots:
    void printTime(unsigned _time) {
        qDebug() << "=============time: " << _time << " ============";
    }

    void printValue(double _value) {
        qDebug() << "=============value: " << _value << " ============";
    }

    void printResume() {
        qDebug() << "resume...";
    }

    void printFinish() {
        qDebug() << "=============finish============";
    }

    void printRestart() {
        qDebug() << "restart...";
    }

    void printCancel() {
        qDebug() << "cancel...";
    }

    void printPause() {
        qDebug() << "pause...";
    }

    void printStart() {
         qDebug() << "start...";
    }
};

#endif // GUI_H
