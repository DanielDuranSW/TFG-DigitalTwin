// StateSignalHandler.cpp
#include "StateSignalHandler.h"

StateSignalHandler::StateSignalHandler(QObject *parent) : QObject(parent) {}

void StateSignalHandler::onWorking(const QString &circleName, bool b)
{
    // Emite la señal de cambio de color del círculo indicando que el FSR está trabajando
    emit circleColorChanged(circleName, b);
}

void StateSignalHandler::onWorkingBuffer(const QString &figureName, bool b)
{
    // Emite la señal de cambio de color del círculo indicando que el FSR está trabajando
    emit rectangleColorChanged(figureName, b);
}

void StateSignalHandler::intensityToChange(float intensityValue)
{
    // Emite la señal de cambio de intensidad
    emit intensityChanged(intensityValue);
}

void StateSignalHandler::classifierStateToChange(const QString &stateName)
{
    emit classifierStateChanged(stateName);
}