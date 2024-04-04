// ManagerGUI.h
#ifndef MANAGERGUI_H
#define MANAGERGUI_H

#include <pthread.h>
#include "mainwindow.h"
#include <QApplication>
#include <cstdio>


struct GUIArguments {
    int argc;
    char** argv;
    StateSignalHandler *stateSignalHandler;
};

void *gui_run(void *arg);

#endif // MANAGERGUI_H
