#include "finddatathread.h"
#include <QTextStream>
#include <QMapIterator>
FindDataThread::FindDataThread()
{

}
FindDataThread::~FindDataThread()
{

}

void FindDataThread::run()
{
     LOGI("finddatathread start");
    QSqlQuery query;
    QString sql="SELECT reportTime,pos,datatype,`data`,pictureType,pictureName FROM tbl_substationdata WHERE terminalId='"+deviceId+"' AND reportTime >='"+starttime+"' AND reportTime <='"+stoptime+"' AND pos >="+startpos+" AND  pos <="+stoppos+" AND pos > 2000 ORDER BY pos,reportTime";
   // qDebug()<<deviceId<<" "<<starttime<<" "<<stoptime<<" "<<startpos<<" "<<stoppos;
    query.exec(sql);
    datamap=new  QMap<int,QList<Substationdata*>*>();
    QMap<int,QList<Substationdata*>*>::iterator mi;
    while(query.next())
    {
         Substationdata *sub=new Substationdata();
         sub->setReportTime(query.value(0).toString());
         int pos=query.value(1).toInt();
         sub->setPos(pos);
         sub->setDatatype(query.value(2).toInt());
         sub->setData(query.value(3).toInt());
         sub->setPictureType(query.value(4).toInt());
         sub->setPictureName(query.value(5).toString());
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
    LOGI("datamap size:"<<datamap->size());
    if(model&&!name.isEmpty())
    {
         QFile file(name);
         if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
         {
             LOGE("�����ļ�����: "<<file.errorString().toStdString());
             emit threadEnd(datamap);
             return;
         }
        QTextStream out(&file);
        LOGI("��ʼ�����ļ�:"<<name.toStdString());
        out<<CH("����ID:,")<<deviceId<<",\n";
        out<<CH("λ��,")<<CH("�ϱ�ʱ��,")<<CH("��������,")<<CH("����,\n");
        QMapIterator<int,QList<Substationdata*>*> i(*datamap);
         while (i.hasNext()) {
                 i.next();
                 const auto &li=i.value();
                 for(int j=0;j<li->size();j++)
                 {
                      auto &tem=li->at(j);
                      out<<tem->getPos()<<","<<tem->getReportTime()<<",";
                     QString types,dat;
                       switch (tem->getDatatype()) {
                       case 0:
                         types=CH("����״̬");
                         dat=tem->getData()==0?CH("��"):CH("��");
                         break;
                      case 1:
                         types=CH("��λ");
                         dat=QString::number(tem->getData());
                         break;
                      case 2:
                         types=CH("����");
                         dat=QString::number(tem->getData());
                         break;
                      default:
                         types=CH("����");
                         dat=QString::number(tem->getData());
                         break;
                      }
                       out<<types<<","<<dat<<",\n";
                 }
               }
       file.close();
       LOGI("�����ļ��ɹ�:"<<name.toStdString());
     }
     emit threadEnd(datamap);
     LOGI("finddataThread exit");
}
