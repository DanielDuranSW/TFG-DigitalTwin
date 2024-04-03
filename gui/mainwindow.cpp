#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QGraphicsEllipseItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) :
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
    QGraphicsEllipseItem *circle1 = new QGraphicsEllipseItem(0, 0, 50, 50);
    circle1->setBrush(Qt::blue); // Establecer color inicial
    scene->addItem(circle1);

    // Crear un círculo en la escena 2
    QGraphicsEllipseItem *circle2 = new QGraphicsEllipseItem(0, 0, 50, 50);
    circle2->setBrush(Qt::blue); // Establecer color inicial
    scene2->addItem(circle2);

    // Configurar temporizador para cambiar el color del círculo 1
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [=]() {
        static bool isBlue = true;
        if (isBlue) {
            circle1->setBrush(Qt::red);
        } else {
            circle1->setBrush(Qt::blue);
        }
        isBlue = !isBlue;
    });
    timer->start(1000); // Cambiar cada segundo

    // Configurar temporizador para cambiar el color del círculo 2
    QTimer *timer2 = new QTimer(this);
    connect(timer2, &QTimer::timeout, [=]() {
        static bool isBlue = true;
        if (isBlue) {
            circle2->setBrush(Qt::red);
        } else {
            circle2->setBrush(Qt::blue);
        }
        isBlue = !isBlue;
    });
    timer2->start(1000); // Cambiar cada medio segundo
}


MainWindow::~MainWindow()
{
    delete ui;
}
