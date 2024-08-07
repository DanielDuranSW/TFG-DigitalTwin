#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsEllipseItem>
#include "StateSignalHandler.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
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
    void onCircleColorChanged(const QString &circleName, bool isWorking);
    void onRectangleColorChanged(const QString &rectangleName, bool isWorking);
    void updateConfigurations();
    void onClassifierStateChanged(const QString &StateName);
    void onIntensityChanged(float intensityValue);

private:
    Ui::MainWindow *ui;
    QMap<QString, QGraphicsScene *> sceneMap;
    QMap<QString, QGraphicsEllipseItem *> circleMap;
    QMap<QString, QGraphicsRectItem *> rectangleMap;
};

#endif // MAINWINDOW_H
