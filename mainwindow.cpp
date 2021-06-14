
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    QTimer *timer = new QTimer(this);
//       connect(timer, &QTimer::timeout, this, &Foo::processOneThing);
//       timer->start();
//    connect(this, SIGNAL(keyPressEvent(QKeyEvent)), ui->openGLWidget, SLOT(keyPressEvent(QKeyEvent) ));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    if(event->key() == Qt::Key::Key_Left)
    {
        ui->openGLWidget->translate(-0.01f, 0.0f);
        ui->openGLWidget->update();
    }

    if(event->key() == Qt::Key::Key_Right)
    {
        ui->openGLWidget->translate(0.01f, 0.0f);
        ui->openGLWidget->update();
    }

    if(event->key() == Qt::Key::Key_Up)
    {
        ui->openGLWidget->translate(0.0f, 0.01f);
        ui->openGLWidget->update();
    }

    if(event->key() == Qt::Key::Key_Down)
    {
        ui->openGLWidget->translate(0.0f, -0.01f);
        ui->openGLWidget->update();
    }

    if(event->key() == Qt::Key::Key_Q)
    {
        ui->openGLWidget->selectedNode -= 1;
        if(ui->openGLWidget->selectedNode < 0)
        {
            ui->openGLWidget->selectedNode = ui->openGLWidget->pl->path.points.size()-1;
        }
        ui->openGLWidget->update();
    }

    if(event->key() == Qt::Key::Key_E)
    {
        ui->openGLWidget->selectedNode += 1;
        if(ui->openGLWidget->selectedNode > ui->openGLWidget->pl->path.points.size()-1)
        {
            ui->openGLWidget->selectedNode = 0;
        }
        ui->openGLWidget->update();
    }


}
