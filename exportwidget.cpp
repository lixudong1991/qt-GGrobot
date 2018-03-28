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

    beginTimeL=new QLabel(CH("��ʼʱ��: "));
    beginTime=new QDateTimeEdit(QDateTime::currentDateTime());
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
    HStrList.push_back(CH("����"));
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
   dataTable->horizontalHeader()->resizeSection(0,(w/2-10)*1/5);
   dataTable->horizontalHeader()->resizeSection(1,(w/2-10)*1/5);
   dataTable->horizontalHeader()->resizeSection(2,(w/2-10)*1/5);
   dataTable->horizontalHeader()->resizeSection(3,(w/2-10)*1/7);
   dataTable->horizontalHeader()->resizeSection(4,(w/2-10)*1/7);
   posbox->setFixedWidth(w/12);
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
     QHash<int,PreinstallPoint*> *p=term->getPointInfo();
     QHashIterator<int,PreinstallPoint*> piter(*p);
     while (piter.hasNext()) {
             piter.next();
             PreinstallPoint * ppoint=piter.value();
             QString names=ppoint->getPosName()+QString::number(ppoint->getPos());
             posNames.insert(names,QString::number(ppoint->getPos()));
             posNumbers.insert(ppoint->getPos(),names);
     }
     QMapIterator<QString,QString> iter(posNames);
     while (iter.hasNext())
     {
       iter.next();
       beginPos->addItem(iter.key());
       endPos->addItem(iter.key());
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
         const auto &li=data->value(posNames.find(s).value().toInt());
         dataTable->setRowCount(li->size());
         QHash<int,PreinstallPoint*> *p=term->getPointInfo();
         QHash<int,PreinstallPoint*>::const_iterator it;
         for(int j=0;j<li->size();j++)
         {
             auto &tem=li->at(j);
             it=p->find(tem->getSonPos());
             QString str,sonstr,datatype,dat;
             if(it!=p->cend())
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
                 dat=CH("����");
             }
             QTableWidgetItem *item0=new QTableWidgetItem(str);
             item0->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item0->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,0,item0);

             QTableWidgetItem *item1=new QTableWidgetItem(sonstr);
             item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item1->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,1,item1);

             QTableWidgetItem *item2=new QTableWidgetItem(tem->getReportTime());
             item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item2->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,2,item2);

             QTableWidgetItem *item3=new QTableWidgetItem(datatype);
             item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item3->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,3,item3);

             QTableWidgetItem *item4=new QTableWidgetItem(dat);
             item4->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             item4->setBackgroundColor(QColor(255,210,166));
             dataTable->setItem(j,4,item4);
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
    downt.exitexec();
    downima->loadingStart(false,"");
    QMessageBox::critical(this,CH("����"),CH("����ͼƬ����"));
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
     int pos=posNames.find(posbox->currentText()).value().toInt();
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
    thr.setStartpos(posNames.find(beginPos->currentText()).value());
    thr.setStoppos(posNames.find(endPos->currentText()).value());
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
               posbox->addItem(posNumbers.find(i.key()).value());
       }
       if(posbox->count()!=0)
       {
           connect(posbox,SIGNAL(currentIndexChanged(QString)),this,SLOT(posSizeChange(QString)));
           posSizeChange(posbox->currentText());
       }
}
