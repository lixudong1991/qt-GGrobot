#include "finddatathread.h"
#include <QTextStream>
#include <QMapIterator>
FindDataThread::FindDataThread()
{

}
FindDataThread::~FindDataThread()
{

}
/***********************************************************************************
函数名:
函数描述:	导出报表界面数据查询线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void FindDataThread::run()
{
     LOGI("finddatathread start");
    QSqlQuery query;
    QString sql="SELECT reportTime,pos,sonPos,datatype,`data`,pictureType,pictureName FROM tbl_substationdata WHERE terminalId='"+deviceId+"' AND writeTime >='"+starttime+"' AND writeTime <='"+stoptime+"' AND pos >="+startpos+" AND  pos <="+stoppos+" AND pos > 2000 ORDER BY pos,writeTime";
    bool tem=false;
    mutex.lock();
    tem=query.exec(sql);
    mutex.unlock();
    datamap=new  QMap<int,QList<Substationdata*>*>();
    QMap<int,QList<Substationdata*>*>::iterator mi;
    if( tem)
    {
        while(query.next())
        {
             Substationdata *sub=new Substationdata();
             sub->setReportTime(query.value(0).toString());
             int pos=query.value(1).toInt();
             sub->setPos(pos);
             sub->setSonPos(query.value(2).toInt());
             sub->setDatatype(query.value(3).toInt());
             sub->setData(query.value(4).toInt());
             sub->setPictureType(query.value(5).toInt());
             sub->setPictureName(query.value(6).toString());
             mi = datamap->find(pos);
             if(mi != datamap->end())
             {
                 mi.value()->append(sub);
             }else
             {
                 QList<Substationdata*>* li=new QList<Substationdata*>();
                 li->append(sub);
                 datamap->insert(pos,li);
             }
        }
    }
     LOGI("datamap size:"<<datamap->size());
    if(model&&!name.isEmpty())
    {
         QFile file(name);
         if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             LOGE("导出文件错误: "<<file.errorString().toStdString());
             emit threadEnd(datamap);
             return;
         }
        QTextStream out(&file);
        LOGI("开始导出文件:"<<name.toStdString());
        out<<CH("机器ID:,")<<deviceId<<",\n";
        out<<CH("设备名称,")<<CH("检测点,")<<CH("上报时间,")<<CH("检测类型,")<<CH("数据,\n");
        QMapIterator<int,QList<Substationdata*>*> i(*datamap);
        QHash<int,PreinstallPoint*>::const_iterator it;
         while (i.hasNext()) {
                 i.next();
                 const auto &li=i.value();
                 for(int j=0;j<li->size();j++)
                 {
                      auto &tem=li->at(j);    
                      it=preinstallPointMap->find(tem->getSonPos());
                      QString str,sonstr,datatype,dat;
                      if(it!=preinstallPointMap->cend())
                      {
                          str=it.value()->getPosName();
                          sonstr=it.value()->getSonPosName();
                          datatype=it.value()->getCheckName();
                      }
                      if(tem->getDatatype()==2)
                      {
                          dat=QString::number(tem->getData()*0.01);
                      }else
                      {
                          dat=CH("正常");
                      }
                      out<<str<<","<<sonstr<<","<<tem->getReportTime()<<","<<datatype<<","<<dat<<",\n";
                 }
               }
       file.close();
       LOGI("导出文件成功:"<<name.toStdString());
     }
     emit threadEnd(datamap);
     LOGI("finddataThread exit");
}
