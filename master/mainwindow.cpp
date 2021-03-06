#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qss_res.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    CommonHelper::setStyle(":qdarkstyle/style.qss");
  //  setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
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
   }
}



