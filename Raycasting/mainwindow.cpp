#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->pushButtonLoadFile->setIcon(QIcon("../Raycasting/folder265.png"));
    ui->pushButtonSaveFile->setIcon(QIcon("../Raycasting/save29.png"));
    ui->pushButtonRender->setIcon(QIcon("../Raycasting/iris.png"));
    ui->pushButtonClear->setIcon(QIcon("../Raycasting/garbage12.png"));

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
}


void MainWindow::loadFile()
{
    std::string filename = QFileDialog::getOpenFileName(this, "Select a scene", "./", "XML .xml (*.xml)", 0, 0).toUtf8().constData();

    if (filename != "")
    {
        Scene scene;
        scene.loadXml(filename.c_str());
    }
}


void MainWindow::saveFile()
{
    std::string filename = QFileDialog::getSaveFileName(this, "Save a scene", "./", "XML .xml (*.xml)", 0, 0).toUtf8().constData();

    if (filename != "")
    {
        //Scene scene;
        //scene.saveXml(filename);
    }
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


void MainWindow::renderScene()
{
    QImage img("paisagens.jpg");
    int w = img.width();
    int h = img.height();
    ui->labelRender->setPixmap(QPixmap::fromImage(img));
    ui->labelRender->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    ui->spinBoxWidth->setValue(w);
    ui->spinBoxHeight->setValue(h);

    ui->tabWidgetMain->setCurrentWidget(ui->tabRaycast);
}


