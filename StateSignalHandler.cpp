// StateSignalHandler.cpp
#include "StateSignalHandler.h"

StateSignalHandler::StateSignalHandler(QObject *parent) : QObject(parent)
{
}

void StateSignalHandler::emitCircleStateChanged(bool state)
{
    emit circleStateChanged(state);
}
