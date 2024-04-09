#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent, StateSignalHandler *stateSignalHandler) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear las escenas y asociarlas con los QGraphicsView
    QMap<QString, QGraphicsScene*> sceneMap;
    sceneMap["Fsr"] = new QGraphicsScene(this);
    sceneMap["Imu"] = new QGraphicsScene(this);
    sceneMap["Ram"] = new QGraphicsScene(this);
    sceneMap["Ble"] = new QGraphicsScene(this);
    sceneMap["Energy"] = new QGraphicsScene(this);
    sceneMap["Custom"] = new QGraphicsScene(this);

    ui->graphicsViewFsr->setScene(sceneMap["Fsr"]);
    ui->graphicsViewImu->setScene(sceneMap["Imu"]);
    ui->graphicsViewRam->setScene(sceneMap["Ram"]);
    ui->graphicsViewBle->setScene(sceneMap["Ble"]);
    ui->graphicsViewEnergy->setScene(sceneMap["Energy"]);
    ui->graphicsViewCustom->setScene(sceneMap["Custom"]);

    ui->graphicsViewFsr->setStyleSheet("background-color: transparent;");
    ui->graphicsViewImu->setStyleSheet("background-color: transparent;");
    ui->graphicsViewRam->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBle->setStyleSheet("background-color: transparent;");
    ui->graphicsViewEnergy->setStyleSheet("background-color: transparent;");
    ui->graphicsViewCustom->setStyleSheet("background-color: transparent;");

    // Crear los círculos y asociarlos con sus respectivas escenas
    QMap<QString, QGraphicsEllipseItem*> circleMap;
    QStringList keys = sceneMap.keys();
    foreach (const QString &key, keys) {
        QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(0, 0, 50, 50);
        circle->setBrush(QColor(33, 144, 255)); // Color inicial
        sceneMap[key]->addItem(circle);
        circleMap[key] = circle;
    }

    // Conectar la señal del StateSignalHandler a la ranura de la MainWindow
    connect(stateSignalHandler, &StateSignalHandler::circleColorChanged, this, &MainWindow::onCircleColorChanged);

    // Guardar los mapas para su uso posterior
    this->sceneMap = sceneMap;
    this->circleMap = circleMap;
}

void MainWindow::onCircleColorChanged(const QString &circleName, bool isWorking)
{
    printf("Cambiar color del círculo %s\n", qPrintable(circleName));
    if (circleMap.contains(circleName)) {
        QGraphicsEllipseItem *circle = circleMap.value(circleName);
        if (isWorking) {
            circle->setBrush(Qt::red);
        } else {
            circle->setBrush(QColor(33, 144, 255));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
