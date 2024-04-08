// mainwindow.h
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "/home/daniduran/ws/TFG-DigitalTwin/StateSignalHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr, StateSignalHandler *handler = nullptr);
    ~MainWindow();

public slots:
    void onCircleColorChanged(bool isWorking);

private:
    Ui::MainWindow *ui;
    QGraphicsEllipseItem *circle1;
};

#endif // MAINWINDOW_H
