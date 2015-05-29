#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButtonLoadFile->setIcon(QIcon("../assets/icons/folder265.png"));
    ui->pushButtonSaveFile->setIcon(QIcon("../assets/icons/save29.png"));
    ui->pushButtonRender->setIcon(QIcon("../assets/icons/iris.png"));
    ui->pushButtonClear->setIcon(QIcon("../assets/icons/garbage12.png"));

    createConnections();

    QMainWindow::showMaximized();
}


void MainWindow::createConnections()
{
    connect(ui->actionLoad_Scene, SIGNAL(triggered()), this, SLOT(loadFile()));
    connect(ui->actionSave_Scene, SIGNAL(triggered()), this, SLOT(saveFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    connect(ui->actionRender, SIGNAL(triggered()), this, SLOT(renderScene()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(clearScene()));

    connect(ui->pushButtonRender, SIGNAL(clicked()), this, SLOT(renderScene()));
    connect(ui->pushButtonLoadFile, SIGNAL(clicked()), this, SLOT(loadFile()));
    connect(ui->pushButtonSaveFile, SIGNAL(clicked()), this, SLOT(saveFile()));
    connect(ui->pushButtonClear, SIGNAL(clicked()), this, SLOT(clearScene()));
    connect(ui->pushButtonQuit, SIGNAL(clicked()), this, SLOT(close()));

    connect(ui->doubleSpinBoxBackgroundRed, SIGNAL(valueChanged(double)), this, SLOT(changeBackgroundColor()));
    connect(ui->doubleSpinBoxBackgroundGreen, SIGNAL(valueChanged(double)), this, SLOT(changeBackgroundColor()));
    connect(ui->doubleSpinBoxBackgroundBlue, SIGNAL(valueChanged(double)), this, SLOT(changeBackgroundColor()));
}


void MainWindow::loadFile()
{
    std::string filename = QFileDialog::getOpenFileName(this, "Select a scene", "../example/", "XML .xml (*.xml)", 0, 0).toUtf8().constData();

    Scene scene;
    scene.loadXml(filename.c_str());
}


void MainWindow::saveFile()
{
    std::string filename = QFileDialog::getSaveFileName(this, "Save a scene", "./", "XML .xml (*.xml)", 0, 0).toUtf8().constData();

    //Scene scene;
    //scene.saveXml(filename);
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::clearScene()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear scene?",
                                  "Are you sure you want to clear the current scene?\nAll unsaved changes will be lost!",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        ui->labelRender->clear();
    }
    else
    {

    }
}


void MainWindow::changeBackgroundColor()
{
    double r = ui->doubleSpinBoxBackgroundRed->value();
    double g = ui->doubleSpinBoxBackgroundGreen->value();
    double b = ui->doubleSpinBoxBackgroundBlue->value();

    raycastingScene.changeBackgroundColor(r, g, b);
}


void MainWindow::renderScene()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Clear scene?",
                                  "Are you sure you want to clear the current scene?\nAll unsaved changes will be lost!",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes)
    {
        raycastingScene.render();

        QImage img("teste.png");
        int w = img.width();
        int h = img.height();
        ui->labelRender->setPixmap(QPixmap::fromImage(img));
        ui->labelRender->setAlignment(Qt::AlignLeft | Qt::AlignTop);
        ui->spinBoxWidth->setValue(w);
        ui->spinBoxHeight->setValue(h);

        ui->tabWidgetMain->setCurrentWidget(ui->tabRaycast);
    }
    else
    {

    }
}


