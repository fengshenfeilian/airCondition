#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>
#include "datastruct.h"
#include "NetController.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

public:
    explicit MainWindow(QWidget *parent = 0);
    void showLogTable();
    void initializeLog();
    void initializeReport();
    ~MainWindow();

private slots:
    void on_pbsignin_clicked();
    void on_pbsignout_clicked();
    void on_pbstart_clicked();

    void on_pbNetRecord_clicked();

    void on_mode_control_clicked();
    void on_temp_control_clicked();
    void on_slave_state_clicked();


    void on_pbopen_clicked();
    void on_pbshutdown_clicked();

    void on_temp_plus_clicked();
    void on_temp_minus_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pbLogReset_clicked();
    void on_pbLogRefresh_clicked();

    void checkIn(int room_id, QString user_id);
    void checkOut(int room_id, QString user_id);
    void roomIdError();
    void infoIncompleteError();
    void checkOutError();
    void insertTableLog(int room_id, QString check_in_time, QString user_id, double cost);

    void showRoomState();
    void hasOpenError();
    void hasCloseError();
    void openSuccessInfo();
    void closeSuccessInfo();
    void setLbStatusOn();
    void setLbStatusMode();
    void initMainWindow();

    void on_pbModeCold_clicked();
    void on_pbModeWarm_clicked();
    void on_pbReportDay_clicked();
    void on_pbReportWeek_clicked();
    void on_pbReportMon_clicked();

    void enableAccess();
    void unableAccess();
    void setDefaultTemp(int temp);
    void setTempError();
    void setLbTemp(int temp);

    void on_pbExit_clicked();
    void refreshLeUser();
    void checkOutInfo();
    void setModeInfo();
    void initTableRoomState();
    void updateTableRoomState();
    void changeFreq(double value);

    void insertTableRoomState(int room_id, QString user_id);
    void deleteTableRoomState(int room_id);

    void updateTableReport();

    void showTableNetinfo();

private:
    Ui::MainWindow *ui;

    bool workmode;
    int state=SHUTDOWN;
    QSqlTableModel *logModel;
    QSqlTableModel *roomstateModel;
    QSqlTableModel *netinfoModel;

    int DEFAULT_TEMP=25;
    int reportType=0;

    bool m_move;
    QPoint m_startPoint;
    QPoint m_windowPoint;
    QTimer *updateTimer;

    NetController netcon;

};

#endif // MAINWINDOW_H
