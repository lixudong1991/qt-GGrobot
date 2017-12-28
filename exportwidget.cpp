#include "exportwidget.h"
#include <QDate>
#include <QHeaderView>
#include <QFileDialog>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <QDir>
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
    HStrList.push_back(CH("λ��"));
    HStrList.push_back(CH("�ϱ�ʱ��"));
    HStrList.push_back(CH("��������"));
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
void ExportWidget::setLabelSize(int w,int h)
{
   ima->setFixedSize(w/2,h*2/3);
   info->setFixedSize(w/2,h/3);
   dataTable->horizontalHeader()->resizeSection(0,(w/2-10)/8);
   dataTable->horizontalHeader()->resizeSection(1,(w/2-10)*3/8);
   dataTable->horizontalHeader()->resizeSection(2,(w/2-10)*1/8);
   dataTable->horizontalHeader()->resizeSection(3,(w/2-10)*2/8);

}

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
void ExportWidget::initData()
{
    for(const Userterminal &userdevice: *userDevices)
    {
        deviceId->addItem(userdevice.getTerminalId());
    }
    deviceIdchange(deviceId->currentIndex());
    exportbt->setEnabled(true);
    selectbt->setEnabled(true);
    LOGI("exportdownthread start------------------------------------->");
    downt.start();
}
void ExportWidget::deviceIdchange(int i)
{
     beginPos->clear();
     endPos->clear();
    int possize=userDevices->at(i).getPosSize();
    int j=1;
    while(possize)
    {
        beginPos->addItem(QString::number(j++));
        endPos->addItem(QString::number(possize--));
    }
}
void ExportWidget::posSizeChange(QString s)
{

         dataTable->clearContents();
         const auto &li=data->value(s.toInt());
         dataTable->setRowCount(li->size());
         for(int j=0;j<li->size();j++)
         {
             auto &tem=li->at(j);
             QTableWidgetItem *item0=new QTableWidgetItem(QString::number(tem->getPos()));
             item0->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             dataTable->setItem(j,0,item0);
             QTableWidgetItem *item1=new QTableWidgetItem(tem->getReportTime());
             item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
             dataTable->setItem(j,1,item1);
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
         QTableWidgetItem *item2=new QTableWidgetItem(types);
         item2->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         dataTable->setItem(j,2,item2);
         QTableWidgetItem *item3=new QTableWidgetItem(dat);
         item3->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         dataTable->setItem(j,3,item3);
         }
}

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
          downt.setName(s);
          downt.wakeT();
          downima->loadingStart(true,CH("��������ͼƬ"));
      }
 }
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
void ExportWidget::selectData()
{
    exportbt->setEnabled(false);
    selectbt->setEnabled(false);
    selectDataThr(false,"");
    downima->loadingStart(true,CH("���ڲ�ѯ..."));
}
void ExportWidget::selectDataThr(bool mode,const QString &file)
{
    thr.setStartTime(beginTime->text());
    thr.setStopTime(endTime->text());
    thr.setDeviceId(userDevices->at(deviceId->currentIndex()).getTerminalId());
    thr.setStartpos(beginPos->currentText());
    thr.setStoppos(endPos->currentText());
    thr.setFilename(file);
    thr.model=mode;
    thr.start();
}

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
