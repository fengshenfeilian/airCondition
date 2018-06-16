#include "qss_res.h"



void CommonHelper::setStyle(const QString &style){
    QFile qss(style);
    if(!qss.open(QFile::ReadOnly | QIODevice::Text)){
        qDebug()<<"Could not open file";
    }
    qApp->setStyleSheet(qss.readAll());
   // qss.close();
}
