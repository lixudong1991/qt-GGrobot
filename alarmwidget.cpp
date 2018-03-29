#include "alarmwidget.h"
#include <QHeaderView>
#include <QFileDialog>
AlarmWidget::AlarmWidget(QWidget *parent) :
    QWidget(parent)
{
    initPanal();
    initLayout();
    initsolts();
}

AlarmWidget::~AlarmWidget()
{
}
void AlarmWidget::initPanal()
{
    deviceIdL=new QLabel(CH("设备ID: "));
    deviceId=new QComboBox();
    beginTimeL=new QLabel(CH("开始时间: "));
    beginTime=new QDateTimeEdit(QDateTime::currentDateTime());
    beginTime->setDisplayFormat(DATEFORMAT);

    endTimeL=new QLabel(CH("结束时间: "));
    endTime=new QDateTimeEdit(QDateTime::currentDateTime().addDays(1));
    endTime->setDisplayFormat(DATEFORMAT);

    selectbt=new QPushButton(CH("查询历史告警"));
    exportbt=new QPushButton(CH("导出历史告警"));
    selectbt->setEnabled(false);
    exportbt->setEnabled(false);

    downima=new ExportDownima(this);

    dataTable=new QTableWidget();
    QStringList  HStrList;
    HStrList.push_back(CH("设备名称"));
    HStrList.push_back(CH("检测点"));
    HStrList.push_back(CH("上报时间"));
    HStrList.push_back(CH("检测类型"));
    HStrList.push_back(CH("数据"));
    HStrList.push_back(CH("状态"));
    HStrList.push_back(CH("处理时间"));
    HStrList.push_back(CH("操作用户"));
    HStrList.push_back(CH("选择"));

    dataTable->horizontalHeader()->setStretchLastSection(true);
    dataTable->horizontalHeader()->setEnabled(false);
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dataTable->setColumnCount(HStrList.count());
    dataTable->setHorizontalHeaderLabels(HStrList);
    dataTable->verticalHeader()->setVisible(true);

    ima=new QLabel();
    ima->setScaledContents(true);

    managebt=new QPushButton(CH("处理"));
    managebt->setEnabled(false);
    selectall=new QCheckBox();
    selectall->setEnabled(false);

}
 void AlarmWidget::initLayout()
 {
    QHBoxLayout *mainhl=new QHBoxLayout(this);

    QVBoxLayout *leftLa=new QVBoxLayout();
    QVBoxLayout *rightLa=new QVBoxLayout();
    mainhl->addLayout(leftLa);
    mainhl->addLayout(rightLa);

    QGroupBox *boxa=new QGroupBox(CH("历史告警查询"));
    QVBoxLayout *lac=new QVBoxLayout();
    boxa->setLayout(lac);

    QHBoxLayout *boxlayout=new QHBoxLayout();
    QGridLayout *boxla=new QGridLayout();
    boxla->addWidget(deviceIdL,0,0);
    boxla->addWidget(deviceId,0,1);
    boxla->addWidget(beginTimeL,1,0);
    boxla->addWidget(beginTime,1,1);
    boxla->addWidget(endTimeL,1,2);
    boxla->addWidget(endTime,1,3);
    boxlayout->addLayout(boxla);

    QHBoxLayout *ld=new QHBoxLayout();
    ld->addStretch();
    boxlayout->addLayout(ld);

    QHBoxLayout *btl=new QHBoxLayout();
    btl->addStretch();
    btl->addWidget(exportbt);
    btl->addWidget(selectbt);

    lac->addLayout(boxlayout);
    lac->addLayout(btl);

    leftLa->addWidget(boxa);

    QGroupBox *databox=new QGroupBox(CH("数据"));
    QVBoxLayout *datala=new QVBoxLayout();
    datala->addWidget(dataTable);
    QHBoxLayout *lb=new QHBoxLayout();
    lb->addStretch();
    lb->addWidget(managebt);
    lb->addWidget(new QLabel(CH("全选")));
    lb->addWidget(selectall);
    datala->addLayout(lb);
    databox->setLayout(datala);
    leftLa->addWidget(databox);

    rightLa->addWidget(ima);
 }
void AlarmWidget::initDevices()
{
    for(const Userterminal &userdevice: *userDevices)
    {
        deviceId->addItem(userdevice.getTerminalId());
    }
    LOGI("alarmdownthread start------------------------------------->");   
    deviceIdchange(deviceId->currentIndex());
    downt.start();
}
void AlarmWidget::setLabelSize(int w,int h)
{
   ima->setFixedSize(w/2,h*2/3);
   int wid=w/2;
   dataTable->horizontalHeader()->resizeSection(0,wid*2/11);
   dataTable->horizontalHeader()->resizeSection(1,wid*2/11);
   dataTable->horizontalHeader()->resizeSection(2,wid*2/10);
   dataTable->horizontalHeader()->resizeSection(3,wid/11);
   dataTable->horizontalHeader()->resizeSection(4,wid/12);
   dataTable->horizontalHeader()->resizeSection(5,wid/12);
   dataTable->horizontalHeader()->resizeSection(6,wid*2/10);
   dataTable->horizontalHeader()->resizeSection(7,wid/11);
   dataTable->horizontalHeader()->resizeSection(8,wid/12);
}
void AlarmWidget::deviceIdchange(int i)
{
    selectbt->setEnabled(true);
    exportbt->setEnabled(true);
    term=&(userDevices->at(i));
    queryt.preinstallPointMap=term->getPointInfo();
}

/***********************************************************************************
函数名:
函数描述:	点击表格中某一行时下载对应的图片
输入参数:
输出参数:
返回值:
************************************************************************************/
 void AlarmWidget::showImage(int row,int)
 {
     QString s=datas->at(row)->getData()->getPictureName();
     QFile file(EXPORTPATH+s);
      if(file.exists())
      {
          QImage *img=new QImage();
           if(img->load(EXPORTPATH+s))
           {
                   ima->setPixmap(QPixmap::fromImage(*img));
            }
           delete img;
      }else{
          downt.downloadFile(s);
          downima->loadingStart(true,CH("正在下载图片"));
      }
 }
 /***********************************************************************************
 函数名:
 函数描述:	图片下载完成时在右边显示图片
 输入参数:
 输出参数:
 返回值:
 ************************************************************************************/
 void AlarmWidget::setImage(QString s)
 {
     downima->loadingStart(false,"");
     QImage *img=new QImage();
      if(img->load(EXPORTPATH+s))
      {
              ima->setPixmap(QPixmap::fromImage(*img));
       }
      delete img;
 }
void AlarmWidget::initsolts()
{
    connect(dataTable,SIGNAL(cellClicked(int,int)),this,SLOT(showImage(int,int)));
    connect(&downt,SIGNAL(finish(QString)),this,SLOT(setImage(QString)));
    connect(selectbt,SIGNAL(clicked(bool)),this,SLOT(selectbt_click()));
    connect(exportbt,SIGNAL(clicked(bool)),this,SLOT(exportCsv()));
    connect(&queryt,SIGNAL(queryfinish(QList<AlarmSubstation*>*)),this,SLOT(queryDatas(QList<AlarmSubstation*>*)));
    connect(selectall,SIGNAL(stateChanged(int)),this,SLOT(checkAll(int)));
    connect(&updatet,SIGNAL(updatastatus(int)),this,SLOT(updateStatus(int)));
    connect(managebt,SIGNAL(clicked(bool)),this,SLOT(managebt_click()));
    connect(deviceId,SIGNAL(currentIndexChanged(int)),SLOT(deviceIdchange(int)));
    connect(downima,SIGNAL(error()),this,SLOT(loadingtimeout()));
}
void AlarmWidget::loadingtimeout()
{
    downt.exitexec();
    downima->loadingStart(false,"");
    QMessageBox::critical(this,CH("错误"),CH("下载图片出错"));
}
void AlarmWidget::selectbt_click()
{
    queryt.setDeviceId(deviceId->currentText());
    queryt.setStartTime(beginTime->text());
    queryt.setStopTime(endTime->text());
    queryt.queryall=false;
    queryt.model=false;
    queryt.start();
    selectbt->setEnabled(false);
    exportbt->setEnabled(false);
}
void AlarmWidget::exportCsv()
{
    QString filename=QFileDialog::getSaveFileName(this,CH("保存文件"),qApp->applicationDirPath() , tr("Files (*.csv)"));
    if( filename.isEmpty())
    {
        QMessageBox::information(this,"info",CH("请输入文件名"));
        return;
    }
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    queryt.setDeviceId(deviceId->currentText());
    queryt.setStartTime(beginTime->text());
    queryt.setStopTime(endTime->text());
    queryt.setFilename(filename);
    queryt.queryall=false;
    queryt.model=true;
    queryt.start();
}
 void AlarmWidget::queryDatas(QList<AlarmSubstation*> * dats)
 {
       this->datas=dats;
       dataTable->clearContents();
       selectbt->setEnabled(true);
       exportbt->setEnabled(true);
       selectall->setEnabled(false);
       managebt->setEnabled(false);
        if(datas==nullptr)
        {
            LOGI("datas null");
            return;
        }
        dataTable->setRowCount(datas->size());
        QHash<int,PreinstallPoint*> *p=term->getPointInfo();
        QHash<int,PreinstallPoint*>::const_iterator it;
        bool nAlarm=true;
         for(int j=0;j<datas->size();j++)
         {
                AlarmSubstation *data=datas->at(j);
                const Substationdata *subdat=data->getData();
                int status=data->getStatus();
                it=p->find(subdat->getSonPos());
                QString str,sonstr,datatype;
                if(it!=p->cend())
                {
                    str=it.value()->getPosName();
                    sonstr=it.value()->getSonPosName();
                    datatype=it.value()->getCheckName();
                }
                QColor color(255,210,166);
                if(status==0)
                {
                    color=QColor(255,128,0);
                    selectall->setEnabled(true);
                    managebt->setEnabled(true);
                    nAlarm=false;
                }
                QTableWidgetItem *item0=new QTableWidgetItem(str);
                item0->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                item0->setBackgroundColor(color);
                dataTable->setItem(j,0,item0);

                QTableWidgetItem *item1=new QTableWidgetItem(sonstr);
                item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item1->setBackgroundColor(color);
                dataTable->setItem(j,1,item1);

                QTableWidgetItem *item2=new QTableWidgetItem(subdat->getReportTime());
                item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item2->setBackgroundColor(color);
                dataTable->setItem(j,2,item2);

                QTableWidgetItem *item3=new QTableWidgetItem(datatype);
                item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item3->setBackgroundColor(color);
                dataTable->setItem(j,3,item3);

                QTableWidgetItem *item4=new QTableWidgetItem(QString::number(subdat->getData()*0.01));
                item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item4->setBackgroundColor(color);
                dataTable->setItem(j,4,item4);

                QTableWidgetItem *item5=new QTableWidgetItem(CH(status==0?"未处理":"已处理"));
                item5->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item5->setBackgroundColor(color);
                dataTable->setItem(j,5,item5);

                QTableWidgetItem *item6=new QTableWidgetItem(status==0?"":data->getChangeTime());
                item6->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item6->setBackgroundColor(color);
                dataTable->setItem(j,6,item6);

                QTableWidgetItem *item7=new QTableWidgetItem(status==0?"":data->getUserName());
                item7->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                 item7->setBackgroundColor(color);
                dataTable->setItem(j,7,item7);

                QTableWidgetItem *item8=new QTableWidgetItem();
                item8->setCheckState(Qt::Unchecked);
                item8->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
                item8->setBackgroundColor(color);
                dataTable->setItem(j,8,item8);
         }
         if(nAlarm)
         {
            emit noAlarm();
         }

 }
 void AlarmWidget::managebt_click()
 {
     int len=datas->size();
     QStringList ids;
     for(int i=0;i<len;i++)
     {
         if(datas->at(i)->getStatus()==0&&dataTable->item(i,8)->checkState()==Qt::Checked)
         {
             ids<<QString::number(datas->at(i)->getId());
         }
     }
     if(ids.size()!=0)
     {
         updatet.setUserid(term->getUserid());
         updatet.setAlarmids(ids);
         updatet.start();
         managebt->setEnabled(false);
         selectall->setEnabled(false);
     }
 }
 void AlarmWidget::updateStatus(int status)
 {
    if(status==0)
    {
        QMessageBox::information(this,CH("提示"),CH("操作成功"));
    }else{
        QMessageBox::information(this,CH("提示"),CH("操作失败"));
    }
    selectall->setChecked(false);
    setCurrentDevice(deviceId->currentIndex());
 }

void AlarmWidget::checkAll()
{
    int len=datas->size();
    auto sta=selectall->checkState();
    for(int i=0;i<len;i++)
    {
        dataTable->item(i,8)->setCheckState(sta);
    }
}
void AlarmWidget::setCurrentDevice(int i)
{
    deviceId->setCurrentIndex(i);
    endTime->setDateTime(QDateTime::currentDateTime());
    queryt.setDeviceId(userDevices->at(i).getTerminalId());
    queryt.queryall=true;
    queryt.model=false;
    queryt.start();
    selectbt->setEnabled(false);
    exportbt->setEnabled(false);
}
