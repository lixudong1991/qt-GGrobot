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
������:
��������:	������ҪԪ�س�ʼ��
�������:
�������:
����ֵ:
************************************************************************************/
void ExportWidget::initLabel()
{
    deviceIdL=new QLabel(CH("�豸ID: "));
    deviceId=new QComboBox();
    //deviceId->setEditable(true);

    beginTimeL=new QLabel(CH("��ʼʱ��: "));
    beginTime=new QDateTimeEdit(QDate(2017,12,10));
    beginTime->setDisplayFormat(DATEFORMAT);

    endTimeL=new QLabel(CH("����ʱ��: "));
    endTime=new QDateTimeEdit(QDateTime::currentDateTime());
    endTime->setDisplayFormat(DATEFORMAT);

    beginPosL=new QLabel(CH("��ʼλ��: "));
    beginPos=new QComboBox();
    beginPos->setEditable(true);
    endPosL=new QLabel(CH("����λ��: "));
    endPos=new QComboBox();
    endPos->setEditable(true);




    exportbt=new QPushButton(CH("����csv"));
    selectbt=new QPushButton(CH("��ѯ"));
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);

    dataTable=new QTableWidget();
    QStringList  HStrList;
    HStrList.push_back(CH("�豸����"));
    HStrList.push_back(CH("�ϱ�ʱ��"));
    HStrList.push_back(CH("�������"));
    HStrList.push_back(CH("����"));
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
    ter_id=new QLabel(CH("λ��:"));

     ima=new QLabel();
     ima->setScaledContents(true);
     info=new QLabel();

     downima=new ExportDownima(this);
}
/***********************************************************************************
������:
��������:	���õ������������Ԫ�صĴ�С
�������:
�������:
����ֵ:
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
������:
��������:	�������������Ҫ���ֳ�ʼ��
�������:
�������:
����ֵ:
************************************************************************************/
void ExportWidget::initPanal()
{
    QHBoxLayout *mainhl=new QHBoxLayout(this);

    QVBoxLayout *leftLa=new QVBoxLayout();
    QVBoxLayout *rightLa=new QVBoxLayout();
    mainhl->addLayout(leftLa);
    mainhl->addLayout(rightLa);

    QGroupBox *boxa=new QGroupBox(CH("���ݲ�ѯ�͵���"));

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




    QGroupBox *databox=new QGroupBox(CH("����"));
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
������:
��������:	��¼�ɹ�֮���ʼ���û�����,������ͼƬ�����߳�
�������:
�������:
����ֵ:
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
������:
��������:	���ݻ�����id��ȡ��Ӧ�ĵ�ͼλ�õ���Ϣ
�������:
�������:
����ֵ:
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
������:
��������:	������������б���������Ӧ������
�������:
�������:
����ֵ:
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
                 dat=CH("����");
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
������:
��������:	��ʼ��������������ӦԪ�ص��¼�
�������:
�������:
����ֵ:
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
������:
��������:	��������ĳһ��ʱ���ض�Ӧ��ͼƬ
�������:
�������:
����ֵ:
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
          downima->loadingStart(true,CH("��������ͼƬ"));
      }
 }
 /***********************************************************************************
 ������:
 ��������:	ͼƬ�������ʱ���ұ���ʾͼƬ
 �������:
 �������:
 ����ֵ:
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
 ������:
 ��������:	 ��ѯ��ť�¼�,ֻ��ѯ����������
 �������:
 �������:
 ����ֵ:
 ************************************************************************************/
void ExportWidget::selectData()
{
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    selectDataThr(false,"");
    downima->loadingStart(true,CH("���ڲ�ѯ..."));
}
/***********************************************************************************
������:
��������:	�������ݲ�ѯ�߳�
�������:
�������:
����ֵ:
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
������:
��������:	��������,����ѯ����
�������:
�������:
����ֵ:
************************************************************************************/
void ExportWidget::exportCsv()
{
    QString filename=QFileDialog::getSaveFileName(this,CH("�����ļ�"),qApp->applicationDirPath() , tr("Files (*.csv)"));
    if( filename.isEmpty())
    {
        QMessageBox::information(this,"info",CH("�������ļ���"));
        return;
    }
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    selectDataThr(true,filename);
    downima->loadingStart(true,CH("���ڵ���..."));
   // qDebug()<<"filename: "<<filename<<"  " <<"startTime: "<<beginTime->text()<<"  " <<"stopTime: "<<endTime->text()<<"\n"<<"startPos: "<<beginPos->currentText()<<"  " <<"stopPos: "<<endPos->currentText()<<"  " <<"deviceId: "<<userDevices->at(deviceId->currentIndex()).getTerminalId()<<"\n";
}
/***********************************************************************************
������:
��������:	 ���ݲ�ѯ�̲߳�ѯ�ɹ�������ˢ�½���
�������:
�������:
����ֵ:
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
        QMessageBox::information(this,"info",CH("�����ɹ�"));
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
������:
��������:	 ������ͼ�����ļ���ȡλ�õ���Ϣ
�������:
�������:
����ֵ:
************************************************************************************/
void ExportWidget::parseXML(const QString &fname)
{
    if(fname.isEmpty())
        return;

    QFile file(fname);
    if(!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::information(nullptr, QString("error"),
                                 CH("�򿪵�ͼʧ��"));

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
