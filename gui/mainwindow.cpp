#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QTimer>

QGraphicsEllipseItem *circle1;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
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
    circle1->setBrush(Qt::blue); /* Establecer color inicial */
    scene->addItem(circle1);

    // Configurar temporizador para cambiar el color del círculo 1
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]()
            {
                static bool isBlue = true;
                if (isBlue) {
                    circle1->setBrush(Qt::red);
                } else {
                    circle1->setBrush(Qt::blue);
                }
                isBlue = !isBlue; });
    timer->start(1000); // Cambiar cada segundo
}
/*
void MainWindow::onCircleStateChanged(bool state)
{
    if (state)
    {
        // Cambiar el color del círculo a verde
        circle1->setBrush(Qt::green);
    }
    else
    {
        // Cambiar el color del círculo a rojo
        circle1->setBrush(Qt::red);
    }
}
*/
MainWindow::~MainWindow()
{
    delete ui;
}
