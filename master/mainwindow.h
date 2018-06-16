#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

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

    void on_mode_control_clicked();

    void on_temp_control_clicked();

    void on_slave_state_clicked();


    void on_pbopen_clicked();

    void on_pbshutdown_clicked();

    void on_temp_plus_clicked();

    void on_temp_minus_clicked();

    void on_pbmode_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pbLogReset_clicked();

    void on_pbLogRefresh_clicked();

    void checkIn(int room_id, QString user_id);

    void checkOut(int room_id, QString user_id);
    void roomIdError();
    void infoIncompleteError();
    void checkOutError();
    void updateLog(int room_id, QString check_in_time, QString user_id, double cost);



    void on_pbNetRecord_clicked();

private:
    Ui::MainWindow *ui;

    bool workmode;
    int state;
    QSqlTableModel *log_model;
    QSqlTableModel *roomStateModel;

    int DEFAULT_TEMP=25;
};

#endif // MAINWINDOW_H
