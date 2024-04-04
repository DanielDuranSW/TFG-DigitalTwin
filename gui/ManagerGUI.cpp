// ManagerGUI.cpp
#include "ManagerGUI.h"
#include <QApplication>

#include <cstdio>

void *gui_run(void *arg)
{
    GUIArguments* guiArgs = static_cast<GUIArguments*>(arg);
    QApplication a(guiArgs->argc, guiArgs->argv);
    MainWindow w;
    printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAa\n");
    w.show();
    a.exec(); // Ejecutar el bucle de eventos de la aplicación Qt
    return nullptr;
}
