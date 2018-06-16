#include "mainwindow.h"

void MainWindow::initializeReport()
{

}

/*
温控信息表:  
请求开始时间 | 请求结束时间 |房间号|用户号|时间|是否包含开机请求(0 or 1) | 当前温度 | 目标温度 | 目标风速(1,2,3) |累计费用|



房间信息表:
|房间号|用户号|日期|最近一次空调送风时间|最近一次空调停风时间|当日累计能耗|

#if close_time<open_time

房间状态表(主机运行期间):
|房间号|用户号|当前温度|当前风速|累计费用(用户)

*/



//负载均衡:先来先到
/*

*/



/*
1.用户登记
2.主机控制台(用来处理 开关机/模式设置/升降温/ )
3.从机状态显示
4.报表
*/


/*
//所有数据库表字段的数据类型均为text
room_state:
room_id | user_id | current_temp | current_wind | current_cost



*/















