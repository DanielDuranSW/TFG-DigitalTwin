// StateSignalHandler.h
#ifndef STATESIGNALHANDLER_H
#define STATESIGNALHANDLER_H

#include <QObject>

class StateSignalHandler : public QObject
{
    Q_OBJECT

public:
    explicit StateSignalHandler(QObject *parent = nullptr);

signals:
    void circleStateChanged(bool state);

public slots:
    void emitCircleStateChanged(bool state);
};

#endif // STATESIGNALHANDLER_H
