// StateSignalHandler.h
#ifndef STATESIGNALHANDLER_H
#define STATESIGNALHANDLER_H

#include <QObject>

class StateSignalHandler : public QObject
{
    Q_OBJECT
public:
    explicit StateSignalHandler(QObject *parent = nullptr);
    //StateSignalHandler stateSignalHandler;

signals:
    void circleColorChanged(bool isWorking);

public slots:
    void onFsrWorking(bool b);
    // Implementar ranuras para otros hilos si es necesario
};

#endif // STATESIGNALHANDLER_H
