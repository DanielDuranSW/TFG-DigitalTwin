#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

MainWindow::MainWindow(QWidget *parent, StateSignalHandler *stateSignalHandler) : QMainWindow(parent),
                                                                                  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Crear las escenas y asociarlas con los QGraphicsView
    QMap<QString, QGraphicsScene *> sceneMap;
    sceneMap["Fsr"] = new QGraphicsScene(this);
    sceneMap["Imu"] = new QGraphicsScene(this);
    sceneMap["Ram"] = new QGraphicsScene(this);
    sceneMap["Ble"] = new QGraphicsScene(this);
    sceneMap["Energy"] = new QGraphicsScene(this);
    sceneMap["Custom"] = new QGraphicsScene(this);
    sceneMap["WaitingTransfer"] = new QGraphicsScene(this);
    sceneMap["RamToFlash"] = new QGraphicsScene(this);

    sceneMap["Buffer0"] = new QGraphicsScene(this);
    sceneMap["Buffer1"] = new QGraphicsScene(this);
    sceneMap["Buffer2"] = new QGraphicsScene(this);
    sceneMap["Buffer3"] = new QGraphicsScene(this);
    sceneMap["Buffer4"] = new QGraphicsScene(this);
    sceneMap["Buffer5"] = new QGraphicsScene(this);
    sceneMap["Buffer6"] = new QGraphicsScene(this);
    sceneMap["Buffer7"] = new QGraphicsScene(this);
    sceneMap["Buffer8"] = new QGraphicsScene(this);
    sceneMap["Buffer9"] = new QGraphicsScene(this);
    sceneMap["Buffer10"] = new QGraphicsScene(this);
    sceneMap["Buffer11"] = new QGraphicsScene(this);
    sceneMap["Buffer12"] = new QGraphicsScene(this);
    sceneMap["Buffer13"] = new QGraphicsScene(this);
    sceneMap["Buffer14"] = new QGraphicsScene(this);
    sceneMap["Buffer15"] = new QGraphicsScene(this);

    ui->graphicsViewFsr->setScene(sceneMap["Fsr"]);
    ui->graphicsViewImu->setScene(sceneMap["Imu"]);
    ui->graphicsViewRam->setScene(sceneMap["Ram"]);
    ui->graphicsViewBle->setScene(sceneMap["Ble"]);
    ui->graphicsViewEnergy->setScene(sceneMap["Energy"]);
    ui->graphicsViewCustom->setScene(sceneMap["Custom"]);
    ui->graphicsViewWaitingTransfer->setScene(sceneMap["WaitingTransfer"]);
    ui->graphicsViewRamToFlash->setScene(sceneMap["RamToFlash"]);

    ui->graphicsViewBuffer0->setScene(sceneMap["Buffer0"]);
    ui->graphicsViewBuffer1->setScene(sceneMap["Buffer1"]);
    ui->graphicsViewBuffer2->setScene(sceneMap["Buffer2"]);
    ui->graphicsViewBuffer3->setScene(sceneMap["Buffer3"]);
    ui->graphicsViewBuffer4->setScene(sceneMap["Buffer4"]);
    ui->graphicsViewBuffer5->setScene(sceneMap["Buffer5"]);
    ui->graphicsViewBuffer6->setScene(sceneMap["Buffer6"]);
    ui->graphicsViewBuffer7->setScene(sceneMap["Buffer7"]);
    ui->graphicsViewBuffer8->setScene(sceneMap["Buffer8"]);
    ui->graphicsViewBuffer9->setScene(sceneMap["Buffer9"]);
    ui->graphicsViewBuffer10->setScene(sceneMap["Buffer10"]);
    ui->graphicsViewBuffer11->setScene(sceneMap["Buffer11"]);
    ui->graphicsViewBuffer12->setScene(sceneMap["Buffer12"]);
    ui->graphicsViewBuffer13->setScene(sceneMap["Buffer13"]);
    ui->graphicsViewBuffer14->setScene(sceneMap["Buffer14"]);
    ui->graphicsViewBuffer15->setScene(sceneMap["Buffer15"]);

    ui->graphicsViewFsr->setStyleSheet("background-color: transparent;");
    ui->graphicsViewImu->setStyleSheet("background-color: transparent;");
    ui->graphicsViewRam->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBle->setStyleSheet("background-color: transparent;");
    ui->graphicsViewEnergy->setStyleSheet("background-color: transparent;");
    ui->graphicsViewCustom->setStyleSheet("background-color: transparent;");
    ui->graphicsViewWaitingTransfer->setStyleSheet("background-color: transparent;");
    ui->graphicsViewRamToFlash->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer0->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer1->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer2->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer3->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer4->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer5->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer6->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer7->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer8->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer9->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer10->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer11->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer12->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer13->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer14->setStyleSheet("background-color: transparent;");
    ui->graphicsViewBuffer15->setStyleSheet("background-color: transparent;");

    // Crear los círculos y asociarlos con sus respectivas escenas
    QMap<QString, QGraphicsEllipseItem *> circleMap;
    QMap<QString, QGraphicsRectItem *> rectangleMap;
    QStringList keys = sceneMap.keys();
    foreach (const QString &key, keys)
    {
        if (key.startsWith("Buffer"))
        {
            // Si es un buffer, crea un rectángulo
            QGraphicsRectItem *rectangle = new QGraphicsRectItem(0, 0, 34, 23);
            rectangle->setBrush(QColor(33, 144, 255));
            sceneMap[key]->addItem(rectangle);
            rectangleMap[key] = rectangle;
        }
        else
        {
            // Si no es un buffer, crea un círculo
            QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(0, 0, 50, 50);
            circle->setBrush(QColor(33, 144, 255));
            sceneMap[key]->addItem(circle);
            circleMap[key] = circle;
        }
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
    if (circleMap.contains(circleName))
    {
        QGraphicsEllipseItem *circle = circleMap.value(circleName);
        if (isWorking)
        {
            circle->setBrush(Qt::red);
        }
        else
        {
            circle->setBrush(QColor(33, 144, 255));
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
