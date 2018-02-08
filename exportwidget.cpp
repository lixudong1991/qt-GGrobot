#include "exportwidget.h"
#include <QDate>
#include <QHeaderView>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDir>
#include <QDomComment>
#include <QDomElement>
#include <QDomNode>
#include <QDomNodeList>
#define CH(a) QString::fromLocal8Bit(a)

ExportWidget::ExportWidget(QWidget *parent) :
    QWidget(parent)
{
    initLabel();
    initPanal();
    initsolts();
    QDir dir;
    dir.setPath(EXPORTPATH);
    if(!dir.exists())
    {
        dir.mkpath(EXPORTPATH);
    }
}

ExportWidget::~ExportWidget()
{
    if(data==NULL)
    {
        return;
    }
    QMap<int, QList<Substationdata*>*>::iterator iter;
    for( iter=data->begin(); iter!=data->end(); ++iter)
    {
        const QList<Substationdata*>* tem=iter.value();
        for(auto &i:*tem)
        {
                delete i;
        }
        delete tem;
    }
    delete data;
}
/***********************************************************************************
函数名:
函数描述:	界面主要元素初始化
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::initLabel()
{
    deviceIdL=new QLabel(CH("设备ID: "));
    deviceId=new QComboBox();
    //deviceId->setEditable(true);

    beginTimeL=new QLabel(CH("开始时间: "));
    beginTime=new QDateTimeEdit(QDate(2017,12,10));
    beginTime->setDisplayFormat(DATEFORMAT);

    endTimeL=new QLabel(CH("结束时间: "));
    endTime=new QDateTimeEdit(QDateTime::currentDateTime());
    endTime->setDisplayFormat(DATEFORMAT);

    beginPosL=new QLabel(CH("开始位置: "));
    beginPos=new QComboBox();
    beginPos->setEditable(true);
    endPosL=new QLabel(CH("结束位置: "));
    endPos=new QComboBox();
    endPos->setEditable(true);




    exportbt=new QPushButton(CH("导出csv"));
    selectbt=new QPushButton(CH("查询"));
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);

    dataTable=new QTableWidget();
    QStringList  HStrList;
    HStrList.push_back(CH("设备名称"));
    HStrList.push_back(CH("上报时间"));
    HStrList.push_back(CH("检测类型"));
    HStrList.push_back(CH("数据"));
    dataTable->horizontalHeader()->setStretchLastSection(true);
    dataTable->horizontalHeader()->setEnabled(false);
    dataTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    dataTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    dataTable->setColumnCount(HStrList.count());
    dataTable->setHorizontalHeaderLabels(HStrList);
    dataTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    dataTable->verticalHeader()->setVisible(true);



    posbox=new QComboBox();
    posbox->setFixedWidth(50);
    ter_id=new QLabel(CH("位置:"));

     ima=new QLabel();
     ima->setScaledContents(true);
     info=new QLabel();

     downima=new ExportDownima(this);
}
/***********************************************************************************
函数名:
函数描述:	设置导出报表界面子元素的大小
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::setLabelSize(int w,int h)
{
   ima->setFixedSize(w/2,h*2/3);
   info->setFixedSize(w/2,h/3);
   dataTable->horizontalHeader()->resizeSection(0,(w/2-10)*2/8);
   dataTable->horizontalHeader()->resizeSection(1,(w/2-10)*2/8);
   dataTable->horizontalHeader()->resizeSection(2,(w/2-10)*1/8);
   dataTable->horizontalHeader()->resizeSection(3,(w/2-10)*2/8);

}
/***********************************************************************************
函数名:
函数描述:	导出报表界面主要布局初始化
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::initPanal()
{
    QHBoxLayout *mainhl=new QHBoxLayout(this);

    QVBoxLayout *leftLa=new QVBoxLayout();
    QVBoxLayout *rightLa=new QVBoxLayout();
    mainhl->addLayout(leftLa);
    mainhl->addLayout(rightLa);

    QGroupBox *boxa=new QGroupBox(CH("数据查询和导出"));

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

    boxla->addWidget(beginPosL,2,0);
    boxla->addWidget(beginPos,2,1);
    boxla->addWidget(endPosL,2,2);
    boxla->addWidget(endPos,2,3);

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




    QGroupBox *databox=new QGroupBox(CH("数据"));
    QVBoxLayout *datala=new QVBoxLayout();
    QHBoxLayout *titlela=new QHBoxLayout();
    titlela->addStretch();
    titlela->addWidget(ter_id);
    titlela->addWidget(posbox);

    datala->addLayout(titlela);
    datala->addWidget(dataTable);
    databox->setLayout(datala);

    leftLa->addWidget(boxa);
    leftLa->addWidget(databox);

    rightLa->addWidget(ima);

    rightLa->addWidget(info);


}
/***********************************************************************************
函数名:
函数描述:	登录成功之后初始化用户数据,并启动图片下载线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::initData()
{
    for(const Userterminal &userdevice: *userDevices)
    {
        deviceId->addItem(userdevice.getTerminalId());
    }
    deviceIdchange(deviceId->currentIndex());
    LOGI("exportdownthread start------------------------------------->");
    downt.start();
}

/***********************************************************************************
函数名:
函数描述:	根据机器人id读取对应的地图位置点信息
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::deviceIdchange(int i)
{
     beginPos->clear();
     endPos->clear();
     term=&(userDevices->at(i));
     QString ter=term->getTerminalId();
     parseXML(QString("map/")+ter+".xml");
     QMapIterator<int,QPointF> iter(points);
     while (iter.hasNext()) {
             iter.next();
             beginPos->addItem(QString::number(iter.key()));
             endPos->addItem(QString::number(iter.key()));
     }
     if(beginPos->count()!=0)
     {
         exportbt->setEnabled(true);
         selectbt->setEnabled(true);
     }else{
         exportbt->setEnabled(false);
         selectbt->setEnabled(false);
     }
}

/***********************************************************************************
函数名:
函数描述:	导出报表界面中表格中填入对应的数据
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::posSizeChange(QString s)
{
         dataTable->clearContents();
         const auto &li=data->value(s.toInt());
         dataTable->setRowCount(li->size());
         QHash<int,PreinstallPoint*> *p=term->getPointInfo();
         QHash<int,PreinstallPoint*>::const_iterator it;
         for(int j=0;j<li->size();j++)
         {
             auto &tem=li->at(j);
             it=p->find(tem->getSonPos());
              QString str,datatype,dat;
             if(it!=p->cend())
             {
                 str=it.value()->getPosName();
                 datatype=it.value()->getCheckName();
             }
             if(tem->getDatatype()==2)
             {
                 dat=QString::number(tem->getData()*0.01);
             }else
             {
                 dat=CH("正常");
             }
             QTableWidgetItem *item0=new QTableWidgetItem(str);
             item0->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item0->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,0,item0);
             QTableWidgetItem *item1=new QTableWidgetItem(tem->getReportTime());
             item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item1->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,1,item1);
             QTableWidgetItem *item2=new QTableWidgetItem(datatype);
             item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item2->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,2,item2);
             QTableWidgetItem *item3=new QTableWidgetItem(dat);
             item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item3->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,3,item3);
         }
}
/***********************************************************************************
函数名:
函数描述:	初始化导出报表界面对应元素的事件
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::initsolts()
{
     connect(deviceId,SIGNAL(currentIndexChanged(int)),this,SLOT(deviceIdchange(int)));
     connect(exportbt,SIGNAL(clicked(bool)),SLOT(exportCsv()));
     connect(selectbt,SIGNAL(clicked(bool)),this,SLOT(selectData()));
     connect(&thr,SIGNAL(threadEnd(QMap<int,QList<Substationdata*>*>*)),this,SLOT(getDatamap(QMap<int,QList<Substationdata*>*>*)));
     connect(dataTable,SIGNAL(cellClicked(int,int)),this,SLOT(showImage(int,int)));
     connect(&downt,SIGNAL(finish(QString)),this,SLOT(setImage(QString)));
     connect(downima,SIGNAL(error()),this,SLOT(loadingtimeout()));
}
void ExportWidget::loadingtimeout()
{
  /*  if(downt.isRunning())
    {
        downt.terminate();
        LOGE("exportdownthread terminate");
        downt.wait();
    }*/
    downt.exitexec();
}

/***********************************************************************************
函数名:
函数描述:	点击表格中某一行时下载对应的图片
输入参数:
输出参数:
返回值:
************************************************************************************/

 void ExportWidget::showImage(int row,int)
 {
     int pos=posbox->currentText().toInt();
     QString s=data->value(pos)->at(row)->getPictureName();
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
 void ExportWidget::setImage(QString s)
 {
     downima->loadingStart(false,"");
     QImage *img=new QImage();
      if(img->load(EXPORTPATH+s))
      {
              ima->setPixmap(QPixmap::fromImage(*img));
       }
      delete img;
 }
 /***********************************************************************************
 函数名:
 函数描述:	 查询按钮事件,只查询不导出报表
 输入参数:
 输出参数:
 返回值:
 ************************************************************************************/
void ExportWidget::selectData()
{
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    selectDataThr(false,"");
    downima->loadingStart(true,CH("正在查询..."));
}
/***********************************************************************************
函数名:
函数描述:	启动数据查询线程
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::selectDataThr(bool mode,const QString &file)
{
    thr.setStartTime(beginTime->text());
    thr.setStopTime(endTime->text());
    thr.setDeviceId(userDevices->at(deviceId->currentIndex()).getTerminalId());
    thr.setStartpos(beginPos->currentText());
    thr.setStoppos(endPos->currentText());
    thr.setFilename(file);
    thr.model=mode;
    thr.preinstallPointMap=term->getPointInfo();
    thr.start();
}
/***********************************************************************************
函数名:
函数描述:	导出报表,并查询数据
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::exportCsv()
{
    QString filename=QFileDialog::getSaveFileName(this,CH("保存文件"),qApp->applicationDirPath() , tr("Files (*.csv)"));
    if( filename.isEmpty())
    {
        QMessageBox::information(this,"info",CH("请输入文件名"));
        return;
    }
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    selectDataThr(true,filename);
    downima->loadingStart(true,CH("正在导出..."));
   // qDebug()<<"filename: "<<filename<<"  " <<"startTime: "<<beginTime->text()<<"  " <<"stopTime: "<<endTime->text()<<"\n"<<"startPos: "<<beginPos->currentText()<<"  " <<"stopPos: "<<endPos->currentText()<<"  " <<"deviceId: "<<userDevices->at(deviceId->currentIndex()).getTerminalId()<<"\n";
}
/***********************************************************************************
函数名:
函数描述:	 数据查询线程查询成功后重新刷新界面
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::getDatamap(QMap<int,QList<Substationdata*>*>* v)
{
     if(data!=NULL)
      {
          QMap<int, QList<Substationdata*>*>::iterator iter;
          for( iter=data->begin(); iter!=data->end(); ++iter)
          {
              const QList<Substationdata*>* tem=iter.value();
              for(auto &i:*tem)
              {
                      delete i;
              }
              delete tem;
          }
          delete data;
       }
       dataTable->clearContents();
        data=v;
        downima->loadingStart(false,"");
        QMessageBox::information(this,"info",CH("导出成功"));
        exportbt->setEnabled(true);
        selectbt->setEnabled(true);
        disconnect(posbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(posSizeChange(QString)));
        posbox->clear();
       QMapIterator<int,QList<Substationdata*>*> i(*data);
       while (i.hasNext()) {
               i.next();
               posbox->addItem(QString::number(i.key()));
       }
       if(posbox->count()!=0)
       {
           connect(posbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(posSizeChange(QString)));
           posSizeChange(posbox->currentText());
       }
}
/***********************************************************************************
函数名:
函数描述:	 解析地图配置文件读取位置点信息
输入参数:
输出参数:
返回值:
************************************************************************************/
void ExportWidget::parseXML(const QString &fname)
{
    if(fname.isEmpty())
        return;

    QFile file(fname);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(nullptr, QString("error"),
                                 CH("打开地图失败"));

        return;
    }

    QDomDocument domDocument;
    QString error;
    int row = 0, column = 0;
    if(!domDocument.setContent(&file, false, &error, &row, &column)) {
        QMessageBox::information(nullptr, QString("Error"),
                                 QString("parse file failed at line row and column") +
                                 QString::number(row, 10) + QString(",") +
                                 QString::number(column, 10));
        file.close();
        return;
    }

    if(domDocument.isNull()) {
        QMessageBox::information(nullptr, QString("title"),
                                 QString("document is null!"));

        file.close();
        return;
    }

    const QDomElement domElement = domDocument.documentElement();

    const QString domElementTagName = domElement.tagName();

    if (domElementTagName != "routemap") {
        QMessageBox::information(nullptr, QString("title"),
                                 QString("Root Name is wrong!"));
        file.close();
        return;
    }
    const QDomNodeList pointList = domElement.childNodes();
    for(int i=0;i<pointList.count();i++)
    {
        const QDomNode p =pointList.item(i);
        if(!p.isNull())
        {
            QDomElement elementson = p.toElement();
            if(!elementson.isNull()) {
                if (elementson.hasAttribute("id"))
                {
                    int pid=elementson.attributeNode("id").value().toInt();
                    if(pid>=2000)
                    {
                        const QDomNode fristNode =elementson.firstChild();
                        const QDomNode lastNode =elementson.lastChild();
                        if(!fristNode.isNull()&&!lastNode.isNull())
                        {
                            const QDomElement fristElement = fristNode.toElement();
                            const QDomElement lastElement = lastNode.toElement();
                            if(!fristElement.isNull()&&!lastElement.isNull())
                            {
                                int xp=-1,yp=-1;
                                const QString tagname=fristElement.tagName();
                                const QString tagval=fristElement.text();
                                if(!tagval.isEmpty())
                                {
                                    if(tagname=="x")
                                    {
                                        xp=tagval.toInt();
                                    }else{
                                        yp=tagval.toInt();
                                    }
                                }
                                const QString tagname1=lastElement.tagName();
                                const QString tagval1=lastElement.text();
                                if(!tagval1.isEmpty())
                                {
                                    if(tagname1=="x")
                                    {
                                        xp=tagval1.toInt();
                                    }else{
                                        yp=tagval1.toInt();
                                    }
                                }
                                if(xp!=-1&&yp!=-1)
                                {
                                    points.insert(pid,QPointF(((double)xp)/1000.0,((double)yp)/1000.0));
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
