#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qss_res.h"
#include <QDebug>
#include <QMovie>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CommonHelper::setStyle(":qdarkstyle/style.qss");
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
    initMainWindow();
    m_move = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    setLbStatusOn();
    setLbStatusMode();
    setLbTemp(DEFAULT_TEMP);
    unableAccess();
   /* QMovie *movie = new QMovie("/home/marco/project/airCondition/master/images/movie.gif");
    ui->lbMovie->setMovie(movie);
    movie->start();
*/
}


void MainWindow::on_tabWidget_currentChanged(int index)
{
    switch(index){
    case 0:
        ui->stackedWidget->setCurrentIndex(0);
        break;
    case 1:
        break;
    case 2:
        initializeReport();
        break;
    case 3:
        initializeLog();
        break;
   }
}


void MainWindow::on_pbExit_clicked()
{
    qApp->quit();
}
