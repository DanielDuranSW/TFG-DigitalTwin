// ManagerGUI.h
#ifndef MANAGERGUI_H
#define MANAGERGUI_H

#include <pthread.h>
#include "mainwindow.h"

struct GUIArguments {
    int argc;
    char** argv;
};

void *gui_run(void *arg);

#endif // MANAGERGUI_H
