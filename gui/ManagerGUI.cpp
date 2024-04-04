// ManagerGUI.cpp
#include "ManagerGUI.h"

void *gui_run(void *arg)
{
    GUIArguments* guiArgs = static_cast<GUIArguments*>(arg);
    QApplication a(guiArgs->argc, guiArgs->argv);
    MainWindow w(nullptr, guiArgs->stateSignalHandler);
    printf("GUI va a mostrar interfaz\n");
    w.show();
    a.exec();
    return nullptr;
}
