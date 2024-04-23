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
    void circleColorChanged(const QString &circleName, bool isWorking);
    void rectangleColorChanged(const QString &rectangleName, bool isWorking);

public slots:
    void onWorking(const QString &circleName, bool b);
    void onWorkingBuffer(const QString &figureName, bool b);
};

#endif // STATESIGNALHANDLER_H
