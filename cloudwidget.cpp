#include"cloudwidget.h"
#include <string.h>
#include <QDir>
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>
#include <QFileDialog>
#include "statusdata.h"
//#define SDK_REALPLAY

#ifdef  SDK_REALPLAY
#include "HCNetSdk/plaympeg4.h"
#define RESOLUTION  480*270
static LONG lPort; //ȫ�ֵĲ��ſ�port��
#endif
static HWND hWnd;

CloudWidget::CloudWidget(QWidget *parent) :
    QWidget(parent)
{
    labelinit();
    right_groupinit();
    QFile qss(":/qss/wid");
    qss.open(QFile::ReadOnly);
    setStyleSheet(qss.readAll());
    qss.close();
    QPalette pal;
    pal.setColor(QPalette::Background, qRgb(32,39,52));
    setAutoFillBackground(true);
    setPalette(pal);

    QDir dir;
    dir.setPath("cache");
    if(!dir.exists())
    {
        dir.mkpath("cache");
    }
    dir.setPath(SAVEVEDIO);
    if(!dir.exists())
    {
        dir.mkpath(SAVEVEDIO);
    }
    dir.setPath(SAVEPICTURE);
    if(!dir.exists())
    {
        dir.mkpath(SAVEPICTURE);
    }
    dir.setPath("map");
    if(!dir.exists())
    {
        dir.mkpath("map");
    }

    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    NetDev_Init();

    //��ʼ��sdk
    if(!SHOWIMAGE_Init())
    {
          LOGE("SHOWIMAGE_Init() error");
    }
    //��ͼ��ʾsdk��ʼ��
}


CloudWidget::~CloudWidget()
{

   if(lRealPlayHandle!=-1)
   {
       NET_DVR_StopRealPlay(lRealPlayHandle);
       lRealPlayHandle=-1;
#ifdef  SDK_REALPLAY
       PlayM4_Stop(lPort);
       PlayM4_CloseStream(lPort);
       PlayM4_FreePort(lPort);
#endif
       stopGray();
   }

   if(device_logInfo.getLoginID()!=-1)
   {
       NET_DVR_Logout(device_logInfo.getLoginID());
       device_logInfo.setLoginID(-1);
   }
   NET_DVR_Cleanup();
   NetDev_Cleanup();  //�ͷ�SDK��Դ

   if(m_sShowPort!=-1)
   {
       SHOWIMAGE_FreePort(m_sShowPort);
   }

   SHOWIMAGE_Cleanup();
}
/***********************************************************************************
*������:    	 posinit
*��������:	 ͼ�����Ĳ��ֳ�ʼ��
*�������:
*�������:
*����ֵ:
************************************************************************************/
void CloudWidget::posinit()
{    
    QHBoxLayout *mainla=new QHBoxLayout();
    setLayout(mainla);

    QGridLayout *leftla=new QGridLayout();
    leftla->setSpacing(2);
    QVBoxLayout *rightla=new QVBoxLayout();
    rightla->setSpacing(2);
    mainla->addLayout(leftla);
    mainla->addLayout(rightla);

    leftupLayout=new QStackedLayout();
    leftupLayout->addWidget(normalWid);
    leftupLayout->addWidget(cloudVideo);
    leftupLayout->setCurrentWidget(normalWid);

    QHBoxLayout *cloudLay=new QHBoxLayout();
    cloudLay->addStretch();
    cloudLay->addWidget(cloudL);
    cloudLay->addStretch();
    cloudLay->setContentsMargins(0,0,0,0);
    cloudVideo->setLayout(cloudLay);

    QVBoxLayout *leftupla=new QVBoxLayout();
    leftupla->addWidget(normalImageL);
    leftupla->setContentsMargins(0,0,0,0);
    normalWid->setLayout(leftupla);

    leftla->addLayout(leftupLayout,0,0);  //����

    leftdownLayout=new QStackedLayout();
    leftdownLayout->addWidget(infraredWid);
    leftdownLayout->addWidget(infraredVideo);
    leftdownLayout->setCurrentWidget(infraredWid);

    QHBoxLayout *infraLay=new QHBoxLayout();
    infraLay->addStretch();
    infraLay->addWidget(infraredL);
    infraLay->addStretch();
    infraLay->setContentsMargins(0,0,0,0);
    infraredVideo->setLayout(infraLay);

    QVBoxLayout *leftdownla=new QVBoxLayout();
    leftdownla->addWidget(infraredImageL);
    leftdownla->setContentsMargins(0,0,0,0);
    infraredWid->setLayout(leftdownla);

    leftla->addLayout( leftdownLayout,1,0);  //����

    QVBoxLayout *infoLay=new QVBoxLayout();
    infoLay->addWidget(infoL);
    infoLay->setContentsMargins(0,0,0,0);

    leftla->addLayout(infoLay,0,1);   //����

    QVBoxLayout *rightdownla=new QVBoxLayout();
    rightdownla->addWidget(positionL);
    rightdownla->setContentsMargins(0,0,0,0);
    leftla->addLayout(rightdownla,1,1);  //����

    leftla->setContentsMargins(0,0,0,0);

    devices_log=new QGroupBox(CH("�豸"));
    nonnectCloud=new QGroupBox(CH("��̨"));
    right_cloudCtrl=new QGroupBox(CH("��̨����"));
    right_patrolView=new QGroupBox(CH("�Զ�Ѳ��"));

    int wid=w*0.132-10;

    devices_log->setFixedSize(wid,wid*0.382);
    nonnectCloud->setFixedSize(wid,wid*0.382);
    right_cloudCtrl->setFixedSize(wid,wid*1.911);
    right_patrolView->setFixedSize(wid,wid*0.941);

    rightla->addWidget(devices_log);
    rightla->addWidget(right_patrolView);
    rightla->addWidget(nonnectCloud);
    rightla->addWidget(right_cloudCtrl);

    QHBoxLayout *device=new QHBoxLayout();
    device->addWidget(new QLabel(CH("�豸ID:")));
    deviceid->setFixedWidth(wid*0.58);
    device->addWidget(deviceid);
    devices_log->setLayout(device);

    QHBoxLayout *concloud=new QHBoxLayout();
    concloud->addWidget(log_bt);
    nonnectCloud->setLayout(concloud);

    QGridLayout *rightcloud=new QGridLayout();
    rightcloud->addWidget(opencloudw, 0, 0, 1, 3);
    rightcloud->addWidget(cloudCtrl_up_left,1,0);
    rightcloud->addWidget(cloudCtrl_up,1,1);
    rightcloud->addWidget(cloudCtrl_up_right,1,2);
    rightcloud->addWidget(cloudCtrl_left,2,0);
    rightcloud->addWidget(cloudCtrl_auto,2,1);
    rightcloud->addWidget(cloudCtrl_right,2,2);
    rightcloud->addWidget(cloudCtrl_down_left,3,0);
    rightcloud->addWidget(cloudCtrl_down,3,1);
    rightcloud->addWidget(cloudCtrl_down_right,3,2);
    rightcloud->addWidget(cloudCapture,4,0);
    rightcloud->addWidget(cloudWiperPwron,4,1);
    rightcloud->addWidget(cloudRecord,4,2);
    rightcloud->addWidget(new QLabel(CH("��̨�ٶ�:")),5,0,1,2);
    rightcloud->addWidget(cloudSpeed,5,2,1,1);
    rightcloud->addWidget(new QLabel(CH("����: ")),6,0,1,1);
    rightcloud->addWidget(cloudnormalCamera_focalLeft,6,1,1,1);
    rightcloud->addWidget(cloudnormalCamera_focalRight,6,2,1,1);
    rightcloud->addWidget(new QLabel(CH("���⽹��: ")),7,0,1,2);
    rightcloud->addWidget(infradautoFocus,7,2,1,1);
    right_cloudCtrl->setLayout(rightcloud);

    QVBoxLayout *rightpatrolView=new QVBoxLayout();
    rightpatrolView->addWidget(inspecting_Start_Stop);
    rightpatrolView->addWidget(inspecting_Pause_Continue);
    rightpatrolView->addWidget(inspecting_special);
    right_patrolView->setLayout(rightpatrolView);
}
/***********************************************************************************
������:    	 posinit
��������:	 ͼ�����İ�ť��ʼ��
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::right_groupinit()
{
    log_bt=new QPushButton(CH("����"));
    log_bt->setEnabled(false);
    deviceid=new QComboBox();
    opencloudw=new QPushButton(CH("��ʾ��Ƶ"));
    opencloudw->setEnabled(false);

    cloudCtrl_up=new QPushButton(CH("��"));
    cloudCtrl_down=new QPushButton(CH("��"));
    cloudCtrl_left=new QPushButton(CH("��"));
    cloudCtrl_auto=new QPushButton(CH("�Զ�"));
    cloudCtrl_right=new QPushButton(CH("��"));  
    cloudCtrl_up_left=new QPushButton(CH("����"));
    cloudCtrl_up_right=new QPushButton(CH("����"));
    cloudCtrl_down_left=new QPushButton(CH("����"));
    cloudCtrl_down_right=new QPushButton(CH("����"));
    cloudCapture=new QPushButton(CH("ץͼ"));
    cloudWiperPwron=new QPushButton(CH("����ˢ"));
    cloudRecord=new QPushButton(CH("¼��"));

    cloudSpeed=new QComboBox();


    downima=new ExportDownima(this);

    for(int i=1;i<8;i++)
    {
        cloudSpeed->addItem(QString::number(i));
    }

    cloudnormalCamera_focalLeft=new QPushButton(CH("��"));
    cloudnormalCamera_focalRight=new QPushButton(CH("��"));
    infradautoFocus=new QPushButton(CH("�Զ�"));

    inspecting_Start_Stop=new QPushButton(CH("��ʼѲ��"));
    inspecting_Start_Stop->setEnabled(false);
    inspecting_Pause_Continue=new QPushButton(CH("��ͣѲ��"));
    inspecting_Pause_Continue->setEnabled(false);
    inspecting_special=new QPushButton(CH("�ض�Ѳ��"));
    inspecting_special->setEnabled(false);

    cardsW=new InspectingCardW(this);

    slotsinit();
    setButtonstatus(false);
}
/***********************************************************************************
������:    	 posinit
��������:	 ���Ӱ�ť���źźͲ�
�������:
�������:
����ֵ:
************************************************************************************/
 void CloudWidget::slotsinit()
 {
    connect(log_bt,SIGNAL(clicked(bool)),this,SLOT(log_bt_slot()));
    connect(opencloudw,SIGNAL(clicked(bool)),this,SLOT(opencloudClick()));
    connect(cloudCapture,SIGNAL(clicked(bool)),this,SLOT(cloudCapture_click()));
    connect(cloudWiperPwron,SIGNAL(clicked(bool)),this,SLOT(cloudWiperPwron_click()));
    connect(cloudRecord,SIGNAL(clicked(bool)),this,SLOT(cloudRecord_click()));
    connect(cloudSpeed,SIGNAL(currentIndexChanged(int)),this,SLOT(cloudSpeed_Change(int)));

    connect(cloudCtrl_up,SIGNAL(pressed()),this,SLOT(cloudCtrUp_press()));
    connect(cloudCtrl_down,SIGNAL(pressed()),this,SLOT(cloudCtrDown_press()));
    connect(cloudCtrl_left,SIGNAL(pressed()),this,SLOT(cloudCtrLeft_press()));
    connect(cloudCtrl_right,SIGNAL(pressed()),this,SLOT(cloudCtrRight_press()));
    connect(cloudCtrl_auto,SIGNAL(pressed()),this,SLOT(cloudCtrl_auto_press()));
    connect(cloudCtrl_up_left,SIGNAL(pressed()),this,SLOT(cloudCtrl_up_left_press()));
    connect(cloudCtrl_up_right,SIGNAL(pressed()),this,SLOT(cloudCtrl_up_right_press()));
    connect(cloudCtrl_down_left,SIGNAL(pressed()),this,SLOT(cloudCtrl_down_left_press()));
    connect(cloudCtrl_down_right,SIGNAL(pressed()),this,SLOT(cloudCtrl_down_right_press()));

    connect(cloudCtrl_up,SIGNAL(released()),this,SLOT(cloudCtrUp_released()));
    connect(cloudCtrl_down,SIGNAL(released()),this,SLOT(cloudCtrDown_released()));
    connect(cloudCtrl_left,SIGNAL(released()),this,SLOT(cloudCtrLeft_released()));
    connect(cloudCtrl_right,SIGNAL(released()),this,SLOT(cloudCtrRight_released()));
    connect(cloudCtrl_auto,SIGNAL(released()),this,SLOT(cloudCtrl_auto_released()));
    connect(cloudCtrl_up_left,SIGNAL(released()),this,SLOT(cloudCtrl_up_left_released()));
    connect(cloudCtrl_up_right,SIGNAL(released()),this,SLOT(cloudCtrl_up_right_released()));
    connect(cloudCtrl_down_left,SIGNAL(released()),this,SLOT(cloudCtrl_down_left_released()));
    connect(cloudCtrl_down_right,SIGNAL(released()),this,SLOT(cloudCtrl_down_right_released()));

    connect( cloudnormalCamera_focalLeft,SIGNAL(pressed()),this,SLOT(cloudZoomLeft_press()));
    connect( cloudnormalCamera_focalLeft,SIGNAL(released()),this,SLOT(cloudZoomLeft_released()));
    connect( cloudnormalCamera_focalRight,SIGNAL(pressed()),this,SLOT(cloudZoomRight_press()));
    connect( cloudnormalCamera_focalRight,SIGNAL(released()),this,SLOT(cloudZoomRight_released()));
    connect(infradautoFocus,SIGNAL(clicked(bool)),this,SLOT(infradautoFocus_click()));

    connect(inspecting_Pause_Continue,SIGNAL(clicked(bool)),this,SLOT(inspecting_Pause_ContinueClick()));
    connect(inspecting_Start_Stop,SIGNAL(clicked(bool)),this,SLOT(inspecting_Start_StopClick()));
    connect(inspecting_special,SIGNAL(clicked(bool)),this,SLOT(inspecting_special_Click()));

    connect(cardsW,SIGNAL(checkCards(QList<int>*)),this,SLOT(inspect_send(QList<int>*)));

 }
 /***********************************************************************************
 ������:    	 posinit
 ��������:	 ��ʼ��ͼ������Label
 �������:
 �������:
 ����ֵ:
 ************************************************************************************/
void CloudWidget::labelinit()
{
    normalImageL=new QLabel();
    normalImageL->setScaledContents(true);
    normalWid=new QWidget(this);
    cloudVideo=new QWidget(this);

    QPalette pal;
    pal.setColor(QPalette::Background,Qt::black);
    cloudVideo->setAutoFillBackground(true);
    cloudVideo->setPalette(pal);
    cloudL=new QLabel();

    infoL=new Infowidget();
    cloudL->setScaledContents(true);

    infraredImageL=new QLabel();
    infraredImageL->setScaledContents(true);
    infraredVideo=new QWidget(this);
    infraredVideo->setAutoFillBackground(true);
    infraredVideo->setPalette(pal);
    infraredWid=new QWidget(this);
    infraredL=new  QLabel();
    positionL=new RouteWidget();
    positionL->hide();

}
/***********************************************************************************
������:    	 setLabelSize
��������:	 ����label�Ĵ�С
�������:    wid:label�Ŀ��,  hei:label�ĸ߶�
�������:
����ֵ:
************************************************************************************/
void  CloudWidget::setLabelSize(int wid,int hei)
{
    w=wid;
    h=hei;
    int width=w*0.868;
    normalImageL->setFixedSize((width-40)/2,h/2-18);
    infraredImageL->setFixedSize((width-40)/2,h/2-18);
    cloudL->setFixedSize((width-40)/2-80,h/2-18);
    cloudVideo->setFixedSize((width-40)/2,h/2-18);
    infraredL->setFixedSize((width-40)/2-80,h/2-12);
    infraredVideo->setFixedSize((width-40)/2,h/2-12);
    PLAYVIDEODLG_WIDTH=(width-40)/2-80;
    PLAYVIDEODLG_HIGH=h/2-12;
    px=8+((width-12)/2-11-PLAYVIDEODLG_WIDTH)/2;
    px1=px+PLAYVIDEODLG_WIDTH;
    py=(h-18)/2;
    py1=py+PLAYVIDEODLG_HIGH;
    m_pCursorPoint.x=PLAYVIDEODLG_WIDTH-1;
    m_pCursorPoint.y=PLAYVIDEODLG_HIGH-1;
    infoL->setSize((width-12)/2,h/2-18);
    infoL->hide();
    positionL->setFixedSize((width-15)/2,h/2-12);
    posinit();
}
/***********************************************************************************
������:    	 paintEvent
��������:	 ��ͼ������ϻ�7������
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
   int width=w*0.868;
   painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
   painter.drawLine(QPoint(6,6),QPoint(w-15,6));
   painter.drawLine(QPoint(6,6),QPoint(6,h-16));
   painter.drawLine(QPoint(6,h-18),QPoint(w-15,h-18));
   painter.drawLine(QPoint(w-15,6),QPoint(w-15,h-18));
   painter.drawLine(QPoint(width-12,6),QPoint(width-12,h-18));
   painter.drawLine(QPoint((width-12)/2-4,6),QPoint((width-12)/2-4,h-18));
   painter.drawLine(QPoint(6,(h-18)/2),QPoint(width-12,(h-18)/2));
}
/***********************************************************************************
������:    	 log_bt_slot
��������:	 ��̨��½,��������ͷ��ȡ�˿ڲ�������ʾ���
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::log_bt_slot()
{
        if(device_logInfo.getLoginID()!=-1)
        {
            return;
        }

        BOOL ret = SHOWIMAGE_GetPort(&m_sShowPort);
        if(ret == FALSE)
        {
                QMessageBox::critical(this,CH("����"),CH("��ȡ����ͼ����ʾ�˿�ʧ��"));
                return;
        }

        SHOWIMAGE_SetShowImageWnd(m_sShowPort,(HWND)infraredL->winId());
        QString ip=term->getCloudIp();
        QString port=term->getCloudPort();
        QString user=term->getCloudUser();
        QString pwd=term->getCloudPwd();

        NET_DVR_USER_LOGIN_INFO struLoginInfo = {0};

        struLoginInfo.bUseAsynLogin = 0; //ͬ����¼��ʽ
        strcpy(struLoginInfo.sDeviceAddress, ip.toStdString().c_str()); //�豸IP��ַ
        struLoginInfo.wPort = port.toInt(); //�豸����˿�
        strcpy(struLoginInfo.sUserName, user.toStdString().c_str()); //�豸��¼�û���
        strcpy(struLoginInfo.sPassword, pwd.toStdString().c_str()); //�豸��¼����

        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

        long loginid=NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
        device_logInfo.setLoginID(loginid);
        if (loginid < 0)
        {
               QMessageBox::critical(this,CH("����"),CH("������̨ʧ��, �������: ")+QString::number(NET_DVR_GetLastError()));
               return;
        }

        NET_DVR_IPPARACFG_V40 IpAccessCfg;
        memset(&IpAccessCfg,0,sizeof(IpAccessCfg));
        DWORD  dwReturned;

        NET_DVR_GetDVRConfig(device_logInfo.getLoginID(),NET_DVR_GET_IPPARACFG_V40,0,&IpAccessCfg,sizeof(NET_DVR_IPPARACFG_V40),&dwReturned);
        DwStartDChan=IpAccessCfg.dwStartDChan;
        memset(&m_RawHead,0,sizeof(m_RawHead));
        QMessageBox::information(this,CH("��ʾ "),CH("���ӳɹ�:")+QString::number(loginid));
        log_bt->setEnabled(false);
}

/***********************************************************************************
������:    	 initTerminal
��������:	 ��ʼ���û��豸��Ϣ,��������ɨ���߳�,ice������߳�
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::initTerminal()
{
        for(const Userterminal &userdevice: *userDevices)
        {
            deviceid->addItem(userdevice.getTerminalId());
        }
        connect(deviceid,SIGNAL(currentIndexChanged(int)),this,SLOT(deviceidChange(int)));
        connect(&t,SIGNAL(finish(Substationdata*,QList<int>*)),this,SLOT(setLabelIma(Substationdata*,QList<int>*)));
        connect(&t,SIGNAL(queryErr()),this,SLOT(querError()));
        positionL->show();
        deviceidChange(deviceid->currentIndex());
        t.tStart();
        connect(&sportServerT,SIGNAL(comStatus(int,int)),this,SLOT());
        connect(&sportT,SIGNAL(execComStatus(QString)),this,SLOT(setInspectingStatus(QString)));
        sportServerT.start();
        sportT.start();
        infoL->show();
        log_bt->setEnabled(true);
        opencloudw->setEnabled(true);
        inspecting_Start_Stop->setEnabled(true);
        inspecting_Pause_Continue->setEnabled(true);
        inspecting_special->setEnabled(true);
}

void CloudWidget::querError()
{
    QMessageBox::information(this,CH("����"),CH("�����쳣"));
    emit exitprocess();
}
/***********************************************************************************
������:    	 deviceidChange
��������:	 �л�����,ֹͣ��̨��Ƶ�ͺ�����Ƶ,����iceͨ�ŵ�ַ�Ͷ˿�,���ص�ͼ
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::deviceidChange(int i)
{
    log_bt->setEnabled(true);
    term=&(userDevices->at(i));
    t.setTerminalId(term->getTerminalId());
    QString terminIp=term->getTerminalIp();
    QString terminPort=term->getTerminalPort();
    QString arg="robot:tcp -h ";
    arg.append(terminIp);
    arg.append(" -p ");
    arg.append(terminPort);
    LOGI(arg.toStdString().c_str());
    sportT.setProxyArg(arg);
    if(lRealPlayHandle!=-1)
    {
        NET_DVR_StopRealPlay(lRealPlayHandle);
        lRealPlayHandle=-1;
        setButtonstatus(false);
#ifdef  SDK_REALPLAY
        PlayM4_Stop(lPort);
        PlayM4_CloseStream(lPort);
        PlayM4_FreePort(lPort);
#endif
        stopGray();
    }
    if(m_sShowPort!=-1)
    {
        SHOWIMAGE_FreePort(m_sShowPort);
    }
    if(device_logInfo.getLoginID()!=-1)
    {
        NET_DVR_Logout(device_logInfo.getLoginID());
        device_logInfo.setLoginID(-1);
    }
    initCardsW();
    t.setPointInfo(term->getPointInfo());
    int width=w*0.868;
    positionL->setBackImg((width-16)/2,h/2-12,userDevices->at(i).getTerminalId());
}
/***********************************************************************************
������:    	 setLabelIma
��������:	 ���غ������ͨͼƬ����ʾ,����ʾ����Ϣ,������ͼ�ϻ�����ǰ���������˸
�������:   dat:��ǰ�������������Ϣ,is:�������߹��ĵ�
�������:
����ֵ:
************************************************************************************/
void CloudWidget::setLabelIma(Substationdata* dat,QList<int>*is)
{
   infoL->setTerminalId(dat->getTerminalId());
   infoL->setReportTime(dat->getReportTime());
   QHash<int,PreinstallPoint*> *p=term->getPointInfo();
   QHash<int,PreinstallPoint*>::const_iterator it=p->find(dat->getSonPos());;
   QString postr,sonstr,datatype;
   if(dat->getPos()>=2000)
   {
       QImage *img=new QImage();
       if(img->load(FILECACHEPATH+dat->getPictureName()))
        {
            switch (dat->getPictureType()) {
            case 0:
                normalImageL->setPixmap(QPixmap::fromImage(*img));
                break;
            case 1:
                 infraredImageL->setPixmap(QPixmap::fromImage(*img));
                break;
            default:
                break;
            }
        }
       delete  img;
      QFile(FILECACHEPATH+dat->getPictureName()).remove();
       if(it!=p->cend())
       {
           postr=it.value()->getPosName();
           sonstr=it.value()->getSonPosName();
           datatype=it.value()->getCheckName();
           infoL->setData(CH("����"));
       }
   }else if(dat->getPos()>=1000&&dat->getPos()<2000){
      postr=CH("�յ�");  
   }
   infoL->setPos(postr);
   infoL->setSonPos(sonstr);
   infoL->setDatatype(datatype);
   if(dat->getDatatype()==2)
   {
        infoL->setData(QString::number(dat->getData()*0.01));
        if(dat->getData()>=it.value()->getAlarmTemp())
        {
             emit haveAlarm(deviceid->currentIndex());
        }
   }
   StatusData *st=dat->getRobotStatus();
   if(st!=nullptr)
   {
       infoL->setElectricitys(QString::number(st->getElectricitys()*10)+" mA");
       infoL->setVoltage(QString::number(st->getVoltage()*0.01)+" V");
       infoL->setElectricResidue(QString::number(st->getElectricResidue())+" %");
       int s=st->getRobotStatus();
       QString stastr;
       switch (s) {
       case RobotStatus::OFF:
            stastr=CH("����ģʽ");
           break;
       case RobotStatus::DEBUG:
            stastr=CH("����ģʽ");
           break;
       case RobotStatus::AUTO:
            stastr=CH("�Զ�Ѳ��");
           break;
       case RobotStatus::SPECIAL:
            stastr=CH("��Ѳ");
           break;
       case RobotStatus::BACK:
            stastr=CH("����");
           break;
       default:
           break;
       }
       infoL->setRobotStatus(stastr);
   }
   infoL->update();
   if(dat->getPos()!=0)
   {
        positionL->startPoint(dat->getPos(),is);
   } 
}
/***********************************************************************************
������:    	 PTZControlAll
��������:	 ��̨���ƺ���
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed)
{
    if(lRealHandle>=0)
    {
        BOOL ret;
        if(Speed>=1)
        {
            ret = NET_DVR_PTZControlWithSpeed(lRealHandle,dwPTZCommand,dwStop,Speed);
            if(!ret)
            {
                QMessageBox::information(this,CH("��ʾ "),CH("��̨����ʧ��!"));
                return;
            }
        }
        else
        {
            ret = NET_DVR_PTZControl(lRealHandle,dwPTZCommand,dwStop);
            if(!ret)
            {
                QMessageBox::information(this,CH("��ʾ "),CH("��̨����ʧ��!"));
                return;
            }
        }
    }

}
#define lPlayHandle  lRealPlayHandle
/***********************************************************************************
������:    	 cloudCtrUp_press
��������:	 ��̨�ϰ�ť����,��ʼ��̨����
************************************************************************************/
void CloudWidget::cloudCtrUp_press()
{
    PTZControlAll(lPlayHandle,TILT_UP,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrDown_press
��������:	 ��̨�°�ť����,��ʼ��̨����
************************************************************************************/
void CloudWidget::cloudCtrDown_press()
{
    PTZControlAll(lPlayHandle,TILT_DOWN,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrLeft_press
��������:	 ��̨��ť����,��ʼ��̨����
************************************************************************************/
void CloudWidget::cloudCtrLeft_press()
{
    PTZControlAll(lPlayHandle,PAN_LEFT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrUp_press
��������:	 ��̨�Ұ�ť����,��ʼ��̨����
************************************************************************************/
void CloudWidget::cloudCtrRight_press()
{
    PTZControlAll(lPlayHandle,PAN_RIGHT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrUp_press
��������:	 ��̨�ϰ�ť�ɿ�,ֹͣ��̨����
************************************************************************************/
void CloudWidget::cloudCtrUp_released()
{
    PTZControlAll(lPlayHandle,TILT_UP,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrDown_released
��������:	    ��̨�°�ť�ɿ�,ֹͣ��̨����
************************************************************************************/
void CloudWidget::cloudCtrDown_released()
{

    PTZControlAll(lPlayHandle,TILT_DOWN,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrLeft_released
��������:	     ��̨��ť�ɿ�,ֹͣ��̨����
************************************************************************************/
void CloudWidget::cloudCtrLeft_released()
{
    PTZControlAll(lPlayHandle,PAN_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrRight_released
��������:	     ��̨�Ұ�ť�ɿ�,ֹͣ��̨����
************************************************************************************/
void CloudWidget::cloudCtrRight_released()
{
    PTZControlAll(lPlayHandle,PAN_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudZoomLeft_press
��������:	  ��̨������,����
************************************************************************************/
void CloudWidget::cloudZoomLeft_press()
{
    PTZControlAll(lPlayHandle,ZOOM_IN,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudZoomLeft_released
��������:	  ��̨������,�ɿ�
************************************************************************************/
void CloudWidget::cloudZoomLeft_released()
{
    PTZControlAll(lPlayHandle,ZOOM_IN,1,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudZoomRight_press
��������:	  ��̨������,����
************************************************************************************/
void CloudWidget::cloudZoomRight_press()
{
    PTZControlAll(lPlayHandle,ZOOM_OUT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudZoomRight_released
��������:	  ��̨������,�ɿ�
************************************************************************************/
void CloudWidget::cloudZoomRight_released()
{
    PTZControlAll(lPlayHandle,ZOOM_OUT,1,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrl_auto_press
��������:	  ��̨�Զ�����
************************************************************************************/
void CloudWidget::cloudCtrl_auto_press()
{
    PTZControlAll(lPlayHandle,PAN_AUTO,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrl_up_left_press
��������:	  ��̨����,����
************************************************************************************/
void CloudWidget::cloudCtrl_up_left_press()
{
    PTZControlAll(lPlayHandle,UP_LEFT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrl_up_right_press
��������:	 ��̨����,����
************************************************************************************/
void CloudWidget::cloudCtrl_up_right_press()
{
    PTZControlAll(lPlayHandle,UP_RIGHT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrl_down_left_press
��������:	  ��̨����,����
************************************************************************************/
void CloudWidget::cloudCtrl_down_left_press()
{
    PTZControlAll(lPlayHandle,DOWN_LEFT,0,iPTZSpeed);
}
/***********************************************************************************
������:    	 cloudCtrl_down_right_press
��������:	 ��̨����,����
************************************************************************************/
void CloudWidget::cloudCtrl_down_right_press()
{
    PTZControlAll(lPlayHandle,DOWN_RIGHT,0,iPTZSpeed);

}
/***********************************************************************************
������:    	 cloudCtrl_up_right_press
��������:	  ��̨�Զ�,�ɿ�
************************************************************************************/
void CloudWidget::cloudCtrl_auto_released()
{
    PTZControlAll(lPlayHandle,PAN_AUTO,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrl_up_left_released
��������:	  ��̨����,�ɿ�
************************************************************************************/
void CloudWidget::cloudCtrl_up_left_released()
{
    PTZControlAll(lPlayHandle,UP_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrl_up_right_press
��������:	  ��̨����,�ɿ�
************************************************************************************/
void CloudWidget::cloudCtrl_up_right_released()
{
    PTZControlAll(lPlayHandle,UP_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrl_down_left_released
��������:	  ��̨����,�ɿ�
************************************************************************************/
void CloudWidget::cloudCtrl_down_left_released()
{
    PTZControlAll(lPlayHandle,DOWN_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}
/***********************************************************************************
������:    	 cloudCtrl_down_right_released
��������:	  ��̨����,�ɿ�
************************************************************************************/
void CloudWidget::cloudCtrl_down_right_released()
{
    PTZControlAll(lPlayHandle,DOWN_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
}

/***********************************************************************************
������:    	 setButtonstatus
��������:	 ���ð�ť�Ŀ���/������״̬
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::setButtonstatus(bool b)
{
    cloudnormalCamera_focalLeft->setEnabled(b);
    cloudnormalCamera_focalRight->setEnabled(b);
    cloudCapture->setEnabled(b);
    cloudWiperPwron->setEnabled(b);
    cloudRecord->setEnabled(b);
    cloudCtrl_up->setEnabled(b);
    cloudCtrl_down->setEnabled(b);
    cloudCtrl_left->setEnabled(b);
    cloudCtrl_right->setEnabled(b);
    cloudCtrl_auto->setEnabled(b);
    cloudCtrl_up_left->setEnabled(b);
    cloudCtrl_up_right->setEnabled(b);
    cloudCtrl_down_left->setEnabled(b);
    cloudCtrl_down_right->setEnabled(b);
    infradautoFocus->setEnabled(b);  
}

/***********************************************************************************
������:    	 cloudWiperPwron_click
��������:	 ��ʼ/ֹͣ��ˢ
�������:
�������:
����ֵ:
************************************************************************************/
void  CloudWidget::cloudWiperPwron_click()
{
        static bool v=true;
        if(v)
        {
            cloudWiperPwron->setText(CH("����ˢ"));
            NET_DVR_PTZControl(lRealPlayHandle,WIPER_PWRON,0);
        }
        else
        {
            cloudWiperPwron->setText(CH("����ˢ"));
            NET_DVR_PTZControl(lRealPlayHandle,WIPER_PWRON,1);
        }
        v=!v;
}
/***********************************************************************************
������:    	 cloudRecord_click
��������:	 ��ʼ/ֹͣ��̨¼��
�������:
�������:
����ֵ:
************************************************************************************/
void  CloudWidget::cloudRecord_click()
{
    QString file=SAVEVEDIO+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+".mp4";
    static bool v=true;
    if(v)
    {
        if(!NET_DVR_SaveRealData(lRealPlayHandle,const_cast<char *>(file.toStdString().c_str())))
        {
            QMessageBox::information(this,CH("��ʾ "),CH(("����¼��ʧ��")));
            return;
        }
          cloudRecord->setText(CH("ֹͣ"));
    }
    else
    {
          if(!NET_DVR_StopSaveRealData(lRealPlayHandle))
          {
              QMessageBox::information(this,CH("��ʾ "),CH(("ֹͣ¼��ʧ��")));
              return;
          }
         cloudRecord->setText(CH("����"));
    }
    v=!v;
}
/***********************************************************************************
������:    	 cloudSpeed_Change
��������:	 �ı���̨�ٶ�
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::cloudSpeed_Change(int i)
{
    iPTZSpeed=i+1;
}
#ifdef  SDK_REALPLAY
static void   CALLBACK g_RealDataCallBack_V30(LONG, DWORD dwDataType, BYTE *pBuffer,DWORD dwBufSize,void*)
{
    switch (dwDataType)
    {
    case NET_DVR_SYSHEAD: //ϵͳͷ
        if (!PlayM4_GetPort(&lPort))  //��ȡ���ſ�δʹ�õ�ͨ����
        {
            break;
        }
        //m_iPort = lPort; //��һ�λص�����ϵͳͷ������ȡ�Ĳ��ſ�port�Ÿ�ֵ��ȫ��port���´λص�����ʱ��ʹ�ô�port�Ų���
        if (dwBufSize > 0)
        {
            if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //����ʵʱ������ģʽ
            {
                break;
            }

            if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize,RESOLUTION)) //�����ӿ�
            {
                break;
            }
            if (!PlayM4_Play(lPort, hWnd)) //���ſ�ʼ
            {
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:   //��������
        if (dwBufSize > 0 && lPort != -1)
        {
            if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    default: //��������
        if (dwBufSize > 0 && lPort != -1)
        {
            if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    }
}
#endif
/***********************************************************************************
������:    	 opencloudClick
��������:	 ͼ�����ͼƬ����Ƶ�л�
�������:
�������:
����ֵ:
************************************************************************************/
void  CloudWidget::opencloudClick()
{
    QWidget *current_widget = leftupLayout->currentWidget();
    if(current_widget != cloudVideo)
    {
        if(device_logInfo.getLoginID()==-1)
        {
            QMessageBox::information(this,CH("����"),CH("����������̨"));
            return;
        }
        hWnd =(HWND)cloudL->winId() ;
            //��ȡ���ھ��
         NET_DVR_PREVIEWINFO struPlayInfo = {0};
         struPlayInfo.lChannel= DwStartDChan+1 ;       //Ԥ��ͨ����
         struPlayInfo.dwStreamType = 0;       //0-��������1-��������2-����3��3-����4���Դ�����
         struPlayInfo.dwLinkMode   = 0;       //0- TCP��ʽ��1- UDP��ʽ��2- �ಥ��ʽ��3- RTP��ʽ��4-RTP/RTSP��5-RSTP/HTTP
#ifdef  SDK_REALPLAY
         struPlayInfo.hPlayWnd = NULL;         //��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
         lRealPlayHandle = NET_DVR_RealPlay_V40(device_logInfo.getLoginID(), &struPlayInfo,g_RealDataCallBack_V30, NULL);
#else
         struPlayInfo.hPlayWnd = hWnd;         //��ҪSDK����ʱ�����Ϊ��Чֵ����ȡ��������ʱ����Ϊ��
         lRealPlayHandle = NET_DVR_RealPlay_V40(device_logInfo.getLoginID(), &struPlayInfo,NULL, NULL);
#endif
         if (lRealPlayHandle< 0)
          {
                QMessageBox::information(this,CH("����"),CH("����ʧ��"));
                return;
          }
         opencloudw->setText(CH("��ʾ��Ϣ"));
         leftupLayout->setCurrentWidget(cloudVideo);
         leftdownLayout->setCurrentWidget(infraredVideo);
         startGray();
         setButtonstatus(true);
    }
    else
    {
        if(lRealPlayHandle!=-1)
        {
                NET_DVR_StopRealPlay(lRealPlayHandle);
                lRealPlayHandle=-1;
#ifdef   SDK_REALPLAY
                PlayM4_Stop(lPort);
                PlayM4_CloseStream(lPort);
                PlayM4_FreePort(lPort);
#endif
        }

       stopGray();
       setButtonstatus(false);
       opencloudw->setText(CH("��ʾ��Ƶ"));
       leftupLayout->setCurrentWidget(normalWid);
       leftdownLayout->setCurrentWidget(infraredWid);
    }
}
/***********************************************************************************
������:    	 funRealStream
��������:	 �Ҷ�Ԥ���ص�
�������:
�������:
����ֵ:
************************************************************************************/
void CALLBACK funRealStream(DWORD dwDataType, char* pDataBuffer, DWORD dwDataSize,DWORD dwUser, short)
{
    CloudWidget* pThis = (CloudWidget*)dwUser;
    if(pThis == NULL) return;
    pThis->PushRealData(dwDataType,pDataBuffer,dwDataSize);
}
/***********************************************************************************
������:    	 startGray
��������:	 �Ҷ�Ԥ������
�������:
�������:
����ֵ:
************************************************************************************/
bool CloudWidget::startGray()
{
    if(m_sRealHandle != -1)
    {
        return false;
    }
    //�����豸
    QString grayIp=term->getInfraredIp();
    m_sRealHandle = NetDev_Connect(const_cast<char*>(grayIp.toStdString().c_str()),CONNECT_TYPE_ULIRNET);   //
    if(m_sRealHandle == -1)
    {
        return false;
    }
    //��ʼ��ȡʵʱ����  ,TI35��TI65ϵ���豸
    BOOL ret = NetDev_StartRealStream(m_sRealHandle,STREAM_TYPE_GRAYDATA);
    if(ret == FALSE)
    {
        return false;
    }
    //����ʵʱ���ݻص�  TI35��TI65ϵ���豸
    NetDev_SetRealStreamCallBack(m_sRealHandle,funRealStream,(DWORD)this);
    return true;
}
/***********************************************************************************
������:    	 stopGray
��������:	 �Ҷ�Ԥ��ֹͣ
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::stopGray()
{
    //ֹͣ��ȡʵʱ����  TI35��TI65ϵ���豸
    NetDev_StopRealStream(m_sRealHandle);
    //�Ͽ�����
    NetDev_DisConnect(m_sRealHandle);
    m_sRealHandle = -1;
    memset(&m_RawHead,0,sizeof(m_RawHead));
}
static bool Temperature_GetFrameInfo(byte *pBuffer,DWORD dwBufSize,byte **pData,DWORD *dwDataSize)
{

    if(dwBufSize < 512)
    {
        return false;
    }

    *pData = pBuffer;
    *dwDataSize = dwBufSize-512;//512��β�������ݻ����ǲ��²�����
    return true;
}
/***********************************************************************************
������:    	 PushRealData
��������:	 �Ҷ�Ԥ��ͼ����ʾ,�������¶���ʾ
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::PushRealData(DWORD dwDataType,char *pDataBuffer,DWORD dwDataSize)
{
    switch(dwDataType)
    {
    case AVI_HEAD:
    case AVI_DATA:
        break;
    case GRAY_HEAD://��������ͷ
        if(sizeof(m_RawHead) == dwDataSize)
        {
            memcpy(&m_RawHead,pDataBuffer,dwDataSize);
            SHOWIMAGE_SetImageSize(m_sShowPort,m_RawHead.nDectorImageW,m_RawHead.nDectorImageH);
        }
        break;
    case GRAY_DATA://�������ݲ���
        if(Temperature_GetFrameInfo((byte*)pDataBuffer,dwDataSize,&m_pData,&m_dwDataSize) == TRUE)
        {
            m_pImageBuffer = (unsigned char*)pDataBuffer;
            m_ImageBufferSize = dwDataSize;

            SHOWIMAGE_ShowImage(m_sShowPort, m_pData, m_dwDataSize, 100, 0);
            //���¼����¶�
            CalculateCurSor();
            SetMessage();
        }
        break;
    default:
        break;
    }
}
/***********************************************************************************
������:    	 infradautoFocus_click
��������:	 �Ҷ�Ԥ���Զ�����
�������:
�������:
����ֵ:
************************************************************************************/
 void CloudWidget::infradautoFocus_click()
 {
     if(m_sRealHandle!=-1)
     {
         NetDev_DoAction((short)m_sRealHandle, ULIR_KEY_AUTO_FOCUS);
     }
 }
 /***********************************************************************************
 ������:    	 CalculateCurSor
 ��������:	 ���ݻҶ�ͼ�����¶�
 �������:
 �������:
 ����ֵ:
 ************************************************************************************/
void CloudWidget::CalculateCurSor()
{
    if(m_RawHead.nDectorImageW == 0)return;
    POINT ptnew;
    ptnew.x = m_pCursorPoint.x*m_RawHead.nDectorImageW/PLAYVIDEODLG_WIDTH;
    ptnew.y = m_pCursorPoint.y*m_RawHead.nDectorImageH/PLAYVIDEODLG_HIGH;
    if(ptnew.x>=m_RawHead.nDectorImageW)
    {
        ptnew.x = m_RawHead.nDectorImageW-1;
    }
    if(ptnew.y>=m_RawHead.nDectorImageH)
    {
        ptnew.y = m_RawHead.nDectorImageH-1;
    }
    WORD *pTemp = (WORD *)m_pData;
    m_fCursorTemp = Temperature_Gray2Temp_Once(m_RawHead.nCalcType, pTemp[ptnew.x+m_RawHead.nDectorImageW*ptnew.y], 0.96, m_pImageBuffer, m_ImageBufferSize, 0);
    NET_DEV_FULLRECTPARAM fullTemp;
    memset(&fullTemp,0,sizeof(NET_DEV_FULLRECTPARAM));
    DWORD re;
    if(NetDev_GetConfig(m_sRealHandle,ULIR_MEASURE_GET_MAXTEMP2,(void*)&fullTemp,sizeof(NET_DEV_FULLRECTPARAM),&re))
    {
        m_fullMaxTemp=fullTemp.nMaxtTemp100*0.01;
        m_fullMinTemp=fullTemp.nMinTemp100*0.01;
        m_maxx=((double)fullTemp.nMaxx)/m_RawHead.nDectorImageW;
        m_maxy=((double)fullTemp.nMaxy)/m_RawHead.nDectorImageH;
        m_minx=((double)fullTemp.nMinx)/m_RawHead.nDectorImageW;
        m_miny=((double)fullTemp.nMiny)/m_RawHead.nDectorImageH;
    }
}
/***********************************************************************************
������:    	 SetMessage
��������:	 �Ҷ���Ƶ����ʾ�¶���Ϣ
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::SetMessage()
{
      QString str="<ultemp><pic><max>%1,%2,%3</max><min>%4,%5,%6</min><avg>-0.00<avg></pic>";
      str=str.arg(m_fullMaxTemp, 0, 'g',4)
               .arg(m_maxx, 0, 'g',4)
               .arg(m_maxy, 0, 'g',4)
               .arg(m_fullMinTemp, 0, 'g',4)
               .arg(m_minx, 0, 'g',4)
               .arg(m_miny, 0, 'g',4);
      QString str1="<object0><name></name><type>2</type><pos>0.01,0.01,0.99,0.99</pos><alarm>0</alarm><max>%1,%2,%3</max><min>%4,%5,%6</min><unit>0</unit></object0>";
      str1=str1.arg(m_fullMaxTemp, 0, 'g',4)
               .arg(m_maxx, 0, 'g',4)
               .arg(m_maxy, 0, 'g',4)
               .arg(m_fullMinTemp, 0, 'g',4)
               .arg(m_minx, 0, 'g',4)
               .arg(m_miny, 0, 'g',4);
      QString str2="<CURSOR>%1,%2,%3</CURSOR></ultemp>";
      str2=str2.arg(m_pCursorPoint.x)
                 .arg(m_pCursorPoint.y)
                 .arg(m_fCursorTemp, 0, 'g',4);
     QString  strShowInfo= str+str1+str2;
//    //���Ǽ��������¶�
    SHOWIMAGE_SetObjectMessage(m_sShowPort,const_cast<char*>(strShowInfo.toStdString().c_str()));
}
/***********************************************************************************
������:    	 event
��������:	 �����ͣ�����¶���ʾ����
�������:
�������:
����ֵ:
************************************************************************************/
bool CloudWidget::event(QEvent *et)
{
        if(m_sRealHandle!=-1&&et->type()==QEvent::ToolTip)
       {
            QHelpEvent *help=static_cast<QHelpEvent*>(et);
            int posx=help->pos().x();
            int posy=help->pos().y();
            if(posx>=px&&posx<=px1&&posy>=py&&posy<=py1)
            {
                m_pCursorPoint.x=posx-px;
                m_pCursorPoint.y=posy-py;
                CalculateCurSor();
                SetMessage();
            }
            return true;
        }
        return QWidget::event(et);
}
/***********************************************************************************
������:    	 cloudCapture_click
��������:	 ��̨jpegͼ��ץȡ
�������:
�������:
 ����ֵ:
************************************************************************************/
void  CloudWidget::cloudCapture_click()
{
            QString file=SAVEPICTURE+QDateTime::currentDateTime().toString("yyyyMMddhhmmss")+".jpg";
            //�齨jpg�ṹ
            NET_DVR_JPEGPARA JpgPara = {0};
            JpgPara.wPicSize =0;
            JpgPara.wPicQuality = 0;
            if(NET_DVR_CaptureJPEGPicture(device_logInfo.getLoginID(), DwStartDChan+1, &JpgPara, const_cast<char *>(file.toStdString().c_str())))
            {
                 QMessageBox::information(this,CH("��ʾ "),CH(("ץͼ�ɹ�,�ļ�������:"))+qApp->applicationDirPath()+"/"+SAVEPICTURE);
                 LOGI("ץͼ�ɹ�:"<< qApp->applicationDirPath().toStdString().c_str()<<"/"<<file.toStdString().c_str());
            }
            else
            {
                 QMessageBox::information(this,CH("��ʾ "),CH(("ץͼʧ��")));
                 LOGE("ץͼʧ��");
            }
}
/***********************************************************************************
������:    	 setInspectingStatus
��������:	 ��ʼѲ��,ֹͣѲ��,��ͣѲ��,����Ѳ�� ��ť�л�
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::setInspectingStatus(QString cmd)
 {
    if(cmd==STATUS_TEXUN)
    {
          cardsW->setMsginfo(4);
    }else{
     inspecting_Pause_Continue->setEnabled(true);
     inspecting_Start_Stop->setEnabled(true);
     inspecting_special->setEnabled(true);
     downima->loadingStart(false,"");
     QMessageBox::information(this,CH("��ʾ "),CH("��������ʧ��"));
    }
 }
/***********************************************************************************
 ������:    	 inspecting_Start_StopClick
 ��������:	 ��ʼѲ��,ֹͣѲ�� �����
 �������:
 �������:
 ����ֵ:
 ************************************************************************************/
void CloudWidget::inspecting_Start_StopClick(){
    if( sportT.isRunning() ) {
        sportid = 0;
        inspecting_Pause_Continue->setEnabled(false);
        inspecting_Start_Stop->setEnabled(false);
        inspecting_special->setEnabled(false);
        if( cmdStart_Stop == 0 ){
            downima->loadingStart(true,CH("��ʼ�Զ�Ѳ��"));
            sportT.iceSendCommand(STATUS_STARTAUTO);
        }
        else
        {
            downima->loadingStart(true,CH("���ٷ���"));
            sportT.iceSendCommand(STATUS_QUICKBACK);
        }      
    }
}
/***********************************************************************************
������:    	 inspecting_Pause_ContinueClick
��������:	 ��ͣѲ��,����Ѳ�� �����
�������:
�������:
����ֵ:
************************************************************************************/
void CloudWidget::inspecting_Pause_ContinueClick()
{  
    if(sportT.isRunning())
    {
        sportid=1;
        inspecting_Pause_Continue->setEnabled(false);
        inspecting_Start_Stop->setEnabled(false);
        inspecting_special->setEnabled(false);
        if(cmdPause_Continue==0)
        {
            downima->loadingStart(true,CH("��ͣ�Զ�Ѳ��"));
            sportT.iceSendCommand(STATUS_PAUSEAUTO);
        }
        else
        {
             downima->loadingStart(true,CH("�����Զ�Ѳ��"));
            sportT.iceSendCommand(STATUS_CONTINUEAUTO);
        }
    }
}
void CloudWidget::inspecting_special_Click()
{
//    if(sportT.isRunning())
//    {
//        sportT.iceSendCommand(STATUS_TEXUN,"2022,2032,2041,2052,2062");
//    }
    cardsW->show();
}
void CloudWidget::inspect_send(QList<int> *l)
{
        QString cardsstr;
        for(int i:*l)
        {
           cardsstr.append(QString::number(cardsNum.at(i))).append(",");
        }
        if(cardsstr.length()>0)
        {
            cardsstr.remove(cardsstr.length()-1,1);
            if(sportT.isRunning())
             {
                    sportT.iceSendCommand(STATUS_TEXUN,cardsstr);
             }
        }
}
 void CloudWidget::initCardsW()
 {
        QStringList cardtable;
        cardsNum.clear();
        QMap<int,QString> m;

        QHash<int,PreinstallPoint*> *p=term->getPointInfo();
        QHash<int,PreinstallPoint*>::const_iterator it;
        for(it=p->cbegin();it!=p->cend();++it)
        {
            m.insert(it.value()->getPos(),it.value()->getPosName()+QString::number(it.value()->getPos()));
        }
        QMapIterator<int,QString> iter(m);
        while (iter.hasNext())
        {
                iter.next();
                cardtable.append(iter.value());
                cardsNum.append(iter.key());
        }
        cardsW->setTableData(cardtable);
 }
void CloudWidget::cmdStatus(int c, int s)
{
    LOGI("cloudwidget cmd: "<<c<<" status: "<<s);
    if(c==15)
    {
            cardsW->setMsginfo(s);
    }else
    {
        inspecting_Pause_Continue->setEnabled(true);
        inspecting_Start_Stop->setEnabled(true);
        inspecting_special->setEnabled(true);
        downima->loadingStart(false,"");
        if(sportid==0)
        {
               if(cmdStart_Stop==0)
               {
                    cmdStart_Stop=1;
                    inspecting_Start_Stop->setText(CH("��ʼѲ��"));
               }else
               {
                   cmdStart_Stop=0;
                   inspecting_Start_Stop->setText(CH("���ٷ���"));
               }
        }else{
            if(cmdPause_Continue==0)
            {
                cmdPause_Continue=1;
                inspecting_Pause_Continue->setText(CH("����Ѳ��"));
            }else
            {
                 cmdPause_Continue=0;
                 inspecting_Pause_Continue->setText(CH("��ͣѲ��"));
            }
       }
       QMessageBox::information(this,CH("��ʾ "),CH("��������ɹ�"));
  }

}

