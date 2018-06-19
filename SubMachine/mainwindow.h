#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>
#include <ctime>
#include <QTimer>
#include <QMessageBox>
#include "netcontroller.h"
#include "login.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setRoomID(int newval);
public slots:
    void openFailed();
    void onWindSpeedClick();
    void OpenMachine(int roomid,QJsonObject obj);
    void CloseMachine();
    void ReceiveWind(QJsonObject obj);
    void SetEnergy(QJsonObject);
    void StopWind(QJsonObject);
    void toAwait();
    void restart();
    void handleOpenClose();
    void increaseTargetTemp();
    void decreaseTargetTemp();
    void CheckOut();
    void setFreq(int);

//    void show_mainwindow(QJsonObject);
signals:
    void askWindSupply(int,int,int,int);
    void setisopen(bool);
    void askLogin(int,QString);
    void askLogout(int);
    void state(int,int);
    void stopWindSupply(int);
//    void askLogout2();
private:
//    netController netcon;
//    login log;
    Ui::MainWindow *ui;
    QButtonGroup *windSpeedGroup;
    QTimer *regresstemptimer;
//    QTimer *setdelaytimer;
//    QTimer *judgetimer;

    int isopen;
    int currentmode;//0:coldmode,1:warm mode
    int receivecnt;
    int roomid;
    int roomtemp;
    QString user_id;
    int targettemp,temp_targettemp;
    int currentwindspeed,targetWind;//1:low,2:mid,3:high
    double usedfee;
    double usedenergy;

    void changeWindSpeed(int newspeed);
    void generateRoomTemp();

    int modeCnt[4];
private slots:
    void regressTemp();
    void changeTargetTemp();
    int judgeTemp();
//    void on_OpenClose_clicked();
//    void on_DecreaseTemp_clicked();
};

#endif // MAINWINDOW_H
