#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "constant.h"
#include "netcontroller.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    NetController netcon;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
