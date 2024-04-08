// StateSignalHandler.cpp
#include "StateSignalHandler.h"

StateSignalHandler::StateSignalHandler(QObject *parent) : QObject(parent)
{
    // Constructor
}

void StateSignalHandler::onFsrWorking(bool b)
{
    // Emite la señal de cambio de color del círculo indicando que el FSR está trabajando
    emit circleColorChanged(b);
}
// Implementar ranuras para otros hilos si es necesario
