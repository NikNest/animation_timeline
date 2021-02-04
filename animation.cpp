#include "animation.h"

void Animation::doWork() {
    if (state == PAUSED)
        // treat as resume
        state = RUNNING;

    if (state == RUNNING)
        return;

    state = RUNNING;

    // This loop simulates the actual work
    for (auto i = 0u;  state == RUNNING;  ++i) {
//        qDebug() << i;
        double deltaValue = std::abs(endValue - startValue);
        double speed = deltaValue / (double)duration;
        double stepValue = delay * speed;
        bool end_clause = false;
        if (currentValue + stepValue >= endValue) {
            time = duration;
            currentValue = endValue;
            end_clause = true;
        } else {
            currentValue += stepValue;
        }
        if (time + delay >= duration) {
            time = duration;
            currentValue = endValue;
            end_clause = true;
        } else {
            time += delay;
        }

        emit showValueGUI(currentValue);
        emit showTimeGUI(time);
        QThread::msleep(delay);
        if (isCancelled()) break;
        if (end_clause) {
            break;
        }
    }
    emit finish();
}

void Animation::resume() {
    if (state != PAUSED) {
        return;
    }
    state = RUNNING;
    emit resumePressed();
}

void Animation::pause() {

    auto const dispatcher = QThread::currentThread()->eventDispatcher();
    if (!dispatcher) {
        qCritical() << "thread with no dispatcher";
        return;
    }

    if (state != RUNNING)
        return;

    state = PAUSED;
//    qDebug() << "pause";
    emit pausePressed();
    do {
        dispatcher->processEvents(QEventLoop::WaitForMoreEvents);
    } while (state == PAUSED);
}

void Animation::cancel() {
    if ((state == IDLE) && (currentValue == endValue || time == duration)) {
        return;
    }
    currentValue = endValue;
    time = duration;
    state = IDLE;
//    qDebug() << "cancel";
    emit showTimeGUI(time);
    emit showValueGUI(currentValue);
    emit cancelPressed();
}

void Animation::restart() {
    if ((state == IDLE) && ((currentValue == startValue) || (time == 0)))
        return;
    currentValue = startValue;
    time = 0;
    state = IDLE;
//    qDebug() << "restart";
    emit showTimeGUI(time);
    emit showValueGUI(currentValue);
    emit restartPressed();
}

void Animation::start() {
    if ((state != IDLE) || (currentValue != startValue) || (time != 0)) {
       return;
    }
//    state = RUNNING;
//    qDebug() << "start";
    emit startPressed();
    doWork();
}
