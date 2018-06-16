#ifndef DATASTRUCT_H
#define DATASTRUCT_H
#include <QString>
const int COLDMODE = 0;
const int WARMMODE = 1;

int DEFAULT_TEMP;

enum state_type{
    SHUTDOWN = 0,
    WAIT,
    OPEN
};


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
