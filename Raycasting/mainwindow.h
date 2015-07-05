#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "RaycastingScene.h"
#include "OpenGlScene.h"

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <string>


namespace Ui {
    class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT


    public:

        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();


    public slots:

        void loadFile();
        void saveFile();
        void renderScene();
        void clearScene();
        void changeBackgroundColor();
        void loadTexture();


    private:

        Ui::MainWindow *ui;
        RaycastingScene raycastingScene;
        OpenGlScene openGlScene;

        void createConnections();
};

#endif // MAINWINDOW_H
