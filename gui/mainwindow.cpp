#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QTimer>

QGraphicsEllipseItem *circle1;

MainWindow::MainWindow(QWidget *parent, StateSignalHandler *stateSignalHandler) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear las escenas y asociarlas con los QGraphicsView
    QGraphicsScene *scene = new QGraphicsScene(this);
    QGraphicsScene *scene2 = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView_2->setScene(scene2);

    // Crear un círculo en la escena 1
    circle1 = new QGraphicsEllipseItem(0, 0, 50, 50);
    circle1->setBrush(Qt::blue);
    scene->addItem(circle1);

    // Conectar la señal del StateSignalHandler a la ranura de la MainWindow
    connect(stateSignalHandler, &StateSignalHandler::circleColorChanged, this, &MainWindow::onCircleColorChanged);
}

void MainWindow::onCircleColorChanged(bool isWorking)
{
    // Cambiar el color del círculo en función del estado de trabajo del hilo
    if (isWorking) {
        circle1->setBrush(Qt::green);
    } else {
        circle1->setBrush(Qt::red);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
