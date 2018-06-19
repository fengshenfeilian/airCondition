#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QString>
const int COLDMODE = 0;
const int WARMMODE = 1;


enum state_type{
    SHUTDOWN = 0,
    WAIT,
    OPEN
};
enum ask_type{
    SENDWIND = 0,
    STOPWIND,
    UPDATETEMP,
    ASKLOGIN,
    ASKLOGOUT
};
/*
const double LowWindRate = 0.8
const double MidWindRate = 1.0
const double HighWindRate = 1.3
*/
//不同档位风速单位能耗
const double WindRate[4]={0.0,0.8,1.0,1.3};
//电费费率
//数据表默认刷新频率
 //subMachine info
/*
typedef struct slave_info{
    int room_id;
    QString user_id;
    QString address;
    int current_wind;
    int current_temp;
    double cost;
    double energy;
    int slave_state;
}*/


#endif // DATASTRUCT_H
