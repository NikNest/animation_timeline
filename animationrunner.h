#ifndef ANIMATIONRUNNER_H
#define ANIMATIONRUNNER_H
#include <QThread>
#include "animation.h"

class AnimationRunner : public QObject {
    Q_OBJECT
public:
  explicit AnimationRunner(QObject *parent = 0);

signal:
  void SignalToObj_mainThreadGUI();
  void running();
  void stopped();

public slots:
  void StopWork();
  void StartWork();

private slots:
  void do_Work();

private:
  volatile bool running,stopped;

};

#endif // ANIMATIONRUNNER_H
