#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButtonRender, SIGNAL(clicked()), this, SLOT(render()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));

    QImage img("paisagens.jpg");
    int w = img.width();
    int h = img.height();
    ui->labelRender->setPixmap(QPixmap::fromImage(img));
    ui->labelRender->resize(w, h);
    ui->spinBoxWidth->setValue(w);
    ui->spinBoxHeight->setValue(h);

    PbScene scene;
    if (scene.loadXml("testbeta.xml"))
    {

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::render()
{
    close();
}


