#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlRecord>
#include <QSqlTableModel>
#include <QTableView>


/*
table: logfile
room_id | check_in_time | check_out_time | user_id | cost |

*/

/*
 OnManualSubmit表明我们要提交修改才能使其生效。
 可以先将修改保存起来，当我们执行提交函数时，再去真正地修改数据库。
 当然，这个模型比前面的模型更高级，前面讲的所有操作，在这里都能执行。
*/

void MainWindow::initializeLog()
{
    log_model = new QSqlTableModel(this);
    log_model->setTable("logfile");
    log_model->setHeaderData(log_model->fieldIndex("room_id"),Qt::Horizontal,"房间号");

    log_model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //选取整个表的所有行    
    log_model->select();
    ui->tvLog->setModel(log_model);

}

void MainWindow::showLogTable()
{

}
