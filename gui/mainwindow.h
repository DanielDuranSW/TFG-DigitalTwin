// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "/home/daniduran/ws/TFG-DigitalTwin/State.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onCircleStateChanged(bool state);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
