#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include "config.h"

MainWindow::MainWindow(QWidget *parent, StateSignalHandler *stateSignalHandler) : QMainWindow(parent),
                                                                                  ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditHIGH_FREQ_WAIT->setText(QString::number(1000000 / HIGH_FREQ_WAIT));
    ui->lineEditCOEFFICIENT_RTC->setText(QString::number(COEFFICIENT_RTC));

    // Crear las escenas y asociarlas con los QGraphicsView
    QMap<QString, QGraphicsScene *> sceneMap;
    sceneMap["Fsr"] = new QGraphicsScene(this);
    ui->graphicsViewFsr->setScene(sceneMap["Fsr"]);
    ui->graphicsViewFsr->setStyleSheet("background-color: transparent;");
    sceneMap["Imu"] = new QGraphicsScene(this);
    ui->graphicsViewImu->setScene(sceneMap["Imu"]);
    ui->graphicsViewImu->setStyleSheet("background-color: transparent;");
    sceneMap["Ram"] = new QGraphicsScene(this);
    ui->graphicsViewRam->setScene(sceneMap["Ram"]);
    ui->graphicsViewRam->setStyleSheet("background-color: transparent;");
    sceneMap["Ble"] = new QGraphicsScene(this);
    ui->graphicsViewBle->setScene(sceneMap["Ble"]);
    ui->graphicsViewBle->setStyleSheet("background-color: transparent;");
    sceneMap["Energy"] = new QGraphicsScene(this);
    ui->graphicsViewEnergy->setScene(sceneMap["Energy"]);
    ui->graphicsViewEnergy->setStyleSheet("background-color: transparent;");
    sceneMap["Custom"] = new QGraphicsScene(this);
    ui->graphicsViewCustom->setScene(sceneMap["Custom"]);
    ui->graphicsViewCustom->setStyleSheet("background-color: transparent;");
    sceneMap["WaitingTransfer"] = new QGraphicsScene(this);
    ui->graphicsViewWaitingTransfer->setScene(sceneMap["WaitingTransfer"]);
    ui->graphicsViewWaitingTransfer->setStyleSheet("background-color: transparent;");
    sceneMap["RamToFlash"] = new QGraphicsScene(this);
    ui->graphicsViewRamToFlash->setScene(sceneMap["RamToFlash"]);
    ui->graphicsViewRamToFlash->setStyleSheet("background-color: transparent;");
    sceneMap["Rtc"] = new QGraphicsScene(this);
    ui->graphicsViewRtc->setScene(sceneMap["Rtc"]);
    ui->graphicsViewRtc->setStyleSheet("background-color: transparent;");

    int rectangleWidth = ui->graphicsViewBuffer->width() / BUFFER_SIZE - 2;
    int rectangleHeight = ui->graphicsViewBuffer->height() - 4;

    // Crear un QGraphicsScene y asociarlo con el QGraphicsView
    QGraphicsScene *sceneBuffer = new QGraphicsScene(this);
    ui->graphicsViewBuffer->setScene(sceneBuffer);
    ui->graphicsViewBuffer->setStyleSheet("background-color: transparent;");

    for (int i = 0; i < BUFFER_SIZE; ++i)
    {
        QString bufferKey = QString("Buffer%1").arg(i);
        QGraphicsRectItem *rectangle = sceneBuffer->addRect((i - 1) * rectangleWidth, 0, rectangleWidth, rectangleHeight);
        rectangle->setBrush(QColor(33, 144, 255)); // Color del rectángulo
        rectangle->setPen(QPen(Qt::black, 2));     // Grosor y color del borde
        rectangleMap[bufferKey] = rectangle;
    }
    rectangleWidth = ui->graphicsViewFlash->width() / FLASH_SIZE;
    rectangleHeight = ui->graphicsViewFlash->height() - 4;

    // Crear un QGraphicsScene y asociarlo con el QGraphicsView
    QGraphicsScene *sceneFlash = new QGraphicsScene(this);
    ui->graphicsViewFlash->setScene(sceneFlash);
    ui->graphicsViewFlash->setStyleSheet("background-color: transparent;");

    for (int i = 0; i < FLASH_SIZE; ++i)
    {
        QString flashKey = QString("Flash%1").arg(i);
        QGraphicsRectItem *rectangle = sceneFlash->addRect((i - 1) * rectangleWidth, 0, rectangleWidth, rectangleHeight);
        rectangle->setBrush(QColor(33, 144, 255)); // Color del rectángulo
        rectangle->setPen(QPen(Qt::black, 2));     // Grosor y color del borde
        rectangleMap[flashKey] = rectangle;
    }

    QMap<QString, QGraphicsEllipseItem *> circleMap;
    QStringList keys = sceneMap.keys();
    foreach (const QString &key, keys)
    {

        // Si no es un buffer, crea un círculo
        QGraphicsEllipseItem *circle = new QGraphicsEllipseItem(0, 0, 71, 71);
        circle->setBrush(QColor(33, 144, 255));
        // circle->setPen(QPen(Qt::black, 2)); // Grosor y color del borde
        sceneMap[key]->addItem(circle);
        circleMap[key] = circle;
    }

    // Conectar la señal del StateSignalHandler a la ranura de la MainWindow
    connect(stateSignalHandler, &StateSignalHandler::circleColorChanged, this, &MainWindow::onCircleColorChanged);
    connect(stateSignalHandler, &StateSignalHandler::rectangleColorChanged, this, &MainWindow::onRectangleColorChanged);
    connect(ui->pushButtonUpdateConfigurations, &QPushButton::clicked, this, &MainWindow::updateConfigurations);
    connect(stateSignalHandler, &StateSignalHandler::classifierStateChanged, this, &MainWindow::onClassifierStateChanged);
    connect(stateSignalHandler, &StateSignalHandler::intensityChanged, this, &MainWindow::onIntensityChanged);

    // Guardar los mapas para su uso posterior
    this->sceneMap = sceneMap;
    this->circleMap = circleMap;
    this->sceneMap = sceneMap;
}

void MainWindow::onIntensityChanged(float intensityValue)
{
    ui->labelIntensity->setText(QString::number(intensityValue, 'f', 4));
}

void MainWindow::onClassifierStateChanged(const QString &StateName)
{
    ui->labelClassifierState->setText(StateName);
}

void MainWindow::onCircleColorChanged(const QString &circleName, bool isWorking)
{
    // printf("Cambiar color del círculo %s\n", qPrintable(circleName));
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

void MainWindow::onRectangleColorChanged(const QString &rectangleName, bool isWorking)
{
    // printf("Cambiar color del rectángulo %s\n", qPrintable(rectangleName));
    if (rectangleMap.contains(rectangleName))
    {
        QGraphicsRectItem *rectangle = rectangleMap.value(rectangleName);
        if (isWorking)
        {
            rectangle->setBrush(Qt::red);
        }
        else
        {
            rectangle->setBrush(QColor(33, 144, 255));
        }
    }
}

void MainWindow::updateConfigurations()
{
    // BUFFER_SIZE = ui->lineEditBufferSize->text().toInt();
    HIGH_FREQ_WAIT = 1000000 / ui->lineEditHIGH_FREQ_WAIT->text().toInt();
    COEFFICIENT_RTC = ui->lineEditCOEFFICIENT_RTC->text().toInt();
    STATE_GENERAL_DURATION = HIGH_FREQ_WAIT;

    STATE_FSR_DURATION = HIGH_FREQ_WAIT;
    STATE_IMU_DURATION = HIGH_FREQ_WAIT;
    STATE_RAM_DURATION = HIGH_FREQ_WAIT;
    STATE_BLE_DURATION = HIGH_FREQ_WAIT;
    STATE_ENERGY_DURATION = HIGH_FREQ_WAIT;
    STATE_CUSTOM_DURATION = HIGH_FREQ_WAIT;
    RESOURCE_RTC_DURATION = STATE_GENERAL_DURATION;
    LOW_FREQ_WAIT = HIGH_FREQ_WAIT * COEFFICIENT_RTC;

    printf("Valor de STATE_GENERAL_DURATION: %d\n", STATE_FSR_DURATION);
}

MainWindow::~MainWindow()
{
    delete ui;
}
