#include"cloudwidget.h"
#include <string.h>
#include <QDir>

//#define SDK_REALPLAY

#ifdef  SDK_REALPLAY
#include "HCNetSdk/plaympeg4.h"
#define RESOLUTION  480*270
LONG lPort; //ȫ�ֵĲ��ſ�port��
#endif
HWND hWnd;

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
    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);

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
   }

   if(device_logInfo.getLoginID()!=-1)
   {
       NET_DVR_Logout(device_logInfo.getLoginID());
       device_logInfo.setLoginID(-1);
   }
   NET_DVR_Cleanup();
  // t.tExit();
 //  t.wait();

}
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

    QVBoxLayout *leftupla=new QVBoxLayout();
    leftupla->addWidget(normalImageL);
    leftupla->setContentsMargins(0,0,0,0);
    leftla->addLayout(leftupla,0,0);  //����



    QVBoxLayout *infraredla=new QVBoxLayout();
    infraredla->addWidget(infraredImageL);
     infraredla->setContentsMargins(0,0,0,0);
    leftla->addLayout(infraredla,1,0);  //����

    rightupLayout=new QStackedLayout();
    rightupLayout->addWidget(infoWid);
    rightupLayout->addWidget(cloudVideo);
    rightupLayout->setCurrentWidget(infoWid);

    QVBoxLayout *infoLay=new QVBoxLayout();
    infoLay->addWidget(infoL);
    infoLay->setContentsMargins(0,0,0,0);
    infoWid->setLayout(infoLay);

   QHBoxLayout *cloudLay=new QHBoxLayout();
   cloudLay->addStretch();
   cloudLay->addWidget(cloudL);
   cloudLay->addStretch();
   cloudLay->setContentsMargins(0,0,0,0);
   cloudVideo->setLayout(cloudLay);

   leftla->addLayout(rightupLayout,0,1);   //����

    QVBoxLayout *rightdownla=new QVBoxLayout();
    rightdownla->addWidget(positionL);
     rightdownla->setContentsMargins(0,0,0,0);
    leftla->addLayout(rightdownla,1,1);  //����

    leftla->setContentsMargins(0,0,0,0);

    devices_log=new QGroupBox(CH("�豸"));
    nonnectCloud=new QGroupBox(CH("��̨�͹��ػ�"));
    right_cloudCtrl=new QGroupBox(CH("��̨����"));
    right_patrolView=new QGroupBox(CH("Ѳ��"));

    int wid=w*0.132-10;

    devices_log->setFixedSize(wid,wid*0.382);
    nonnectCloud->setFixedSize(wid,wid*0.382);
    right_cloudCtrl->setFixedSize(wid,wid*1.911);
    right_patrolView->setFixedSize(wid,wid*0.441);

    rightla->addWidget(devices_log);
    rightla->addWidget(right_patrolView);
    rightla->addWidget(nonnectCloud);
    rightla->addWidget(right_cloudCtrl);

    QHBoxLayout *device=new QHBoxLayout();
    device->addWidget(new QLabel(CH("�豸����:")));
    device->addWidget(deviceid);
    devices_log->setLayout(device);

    QHBoxLayout *concloud=new QHBoxLayout();
    concloud->addWidget(log_bt);
    nonnectCloud->setLayout(concloud);

    QGridLayout *rightcloud=new QGridLayout();
        rightcloud->addWidget(new QLabel(CH("����ͷ:")), 0, 0, 1, 1);
        rightcloud->addWidget(nor, 0, 1, 1, 1);
        rightcloud->addWidget(infra, 0, 2, 1, 1);
        rightcloud->addWidget(opencloudw, 1, 0, 1, 3);
        rightcloud->addWidget(cloudCtrl_up_left,2,0);
        rightcloud->addWidget(cloudCtrl_up,2,1);
        rightcloud->addWidget(cloudCtrl_up_right,2,2);
        rightcloud->addWidget(cloudCtrl_left,3,0);
        rightcloud->addWidget(cloudCtrl_auto,3,1);
        rightcloud->addWidget(cloudCtrl_right,3,2);
        rightcloud->addWidget(cloudCtrl_down_left,4,0);
        rightcloud->addWidget(cloudCtrl_down,4,1);
        rightcloud->addWidget(cloudCtrl_down_right,4,2);
        rightcloud->addWidget(cloudCapture,5,0);
        rightcloud->addWidget(cloudWiperPwron,5,1);
        rightcloud->addWidget(cloudRecord,5,2);
        rightcloud->addWidget(new QLabel(CH("��̨�ٶ�:")),6,0,1,2);
        rightcloud->addWidget(cloudSpeed,6,2,1,1);
        rightcloud->addWidget(new QLabel(CH("����: ")),7,0,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalLeft,7,1,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalRight,7,2,1,1);
    right_cloudCtrl->setLayout(rightcloud);



    QVBoxLayout *rightpatrolView=new QVBoxLayout();
    rightpatrolView->addWidget(patrolView_Start);
    right_patrolView->setLayout(rightpatrolView);

}
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
    for(int i=1;i<8;i++)
    {
        cloudSpeed->addItem(QString::number(i));
    }

    nor=new QRadioButton(CH("��ͨ"));
    infra=new QRadioButton(CH("����"));
    normal_infra=new QButtonGroup();
    normal_infra->addButton(nor,0);
    normal_infra->addButton(infra,1);



    cloudnormalCamera_focalLeft=new QPushButton(CH("��"));
    //cloudnormalCamera_focalLeft->setIconSize(pixmap.size());

    cloudnormalCamera_focalRight=new QPushButton(CH("��"));

    patrolView_Start=new QPushButton(CH("ȡ��Ѳ��"));

    slotsinit();
    setButtonstatus(false);

}
 void CloudWidget::slotsinit()
 {
    connect(log_bt,SIGNAL(clicked(bool)),this,SLOT(log_bt_slot()));
    connect(normal_infra,SIGNAL(buttonClicked(int)),this,SLOT(normal_infra_slot(int)));
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
 }

void CloudWidget::labelinit()
{
    normalImageL=new QLabel();
    normalImageL->setScaledContents(true);

    infoWid=new QWidget(this);
    cloudVideo=new QWidget(this);
    QPalette pal;
    pal.setColor(QPalette::Background,Qt::black);
    cloudVideo->setAutoFillBackground(true);
    cloudVideo->setPalette(pal);
    cloudL=new QLabel();
    infoL=new Infowidget();


  //  infoL->setScaledContents(true);
    cloudL->setScaledContents(true);

    infraredImageL=new QLabel();
  //  infraredImageL->setFixedWidth(400);
    infraredImageL->setScaledContents(true);

     positionL=new RouteWidget();
     positionL->hide();
   // positionL=new QLabel();
   // positionL->setScaledContents(true);

}
void  CloudWidget::setLabelSize(int wid,int hei)
{
    w=wid;
    h=hei;
    int width=w*0.868;
    normalImageL->setFixedSize((width-40)/2,h/2-20);
    cloudL->setFixedSize(((h/2-20)/3)*4,h/2-20);
    cloudVideo->setFixedSize((width-16)/2,h/2-20);
    infoL->setSize((width-16)/2,h/2-20);
    infoL->hide();
    positionL->setFixedSize((width-6)/2,h/2-6);
    infraredImageL->setFixedSize((width-40)/2,h/2-20);
    posinit();
}
void CloudWidget::paintEvent(QPaintEvent *)
{
  QPainter painter(this);
   int width=w*0.868;
   painter.setPen(QPen(Qt::white, 1, Qt::SolidLine));
   painter.drawLine(QPoint(6,6),QPoint(w-15,6));
   painter.drawLine(QPoint(6,6),QPoint(6,h-16));
   painter.drawLine(QPoint(6,h-18),QPoint(w-15,h-18));
   painter.drawLine(QPoint(w-15,6),QPoint(w-15,h-18));
   painter.drawLine(QPoint(width-15,6),QPoint(width-15,h-18));
   painter.drawLine(QPoint((width-15)/2-4,6),QPoint((width-15)/2-4,h-18));
   painter.drawLine(QPoint(6,(h-18)/2),QPoint(width-15,(h-18)/2));
}
void CloudWidget::log_bt_slot()
{
        if(device_logInfo.getLoginID()!=-1)
        {
            return;
        }
        const Userterminal &term=userDevices->at(deviceid->currentIndex());
        QString ip=term.getCloudIp();
        QString port=term.getCloudPort();
        QString user=term.getCloudUser();
        QString pwd=term.getCloudPwd();

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


      QMessageBox::information(this,CH("��ʾ "),CH("���ӳɹ�:")+QString::number(loginid));
}


void CloudWidget::initTerminal()
{
        for(const Userterminal &userdevice: *userDevices)
        {
            deviceid->addItem(userdevice.getTerminalId());
        }
        connect(deviceid,SIGNAL(currentIndexChanged(int)),this,SLOT(deviceidChange(int)));
        connect(&t,SIGNAL(finish(Substationdata*)),this,SLOT(setLabelIma(Substationdata*)));
        connect(&t,SIGNAL(queryErr()),this,SLOT(querError()));;
        deviceidChange(deviceid->currentIndex());
        t.tStart();
        infoL->show();


        log_bt->setEnabled(true);
        opencloudw->setEnabled(true);
}

void CloudWidget::querError()
{
    QMessageBox::information(this,CH("����"),CH("�����쳣"));
    exit(0);
}

void CloudWidget::deviceidChange(int i)
{
    t.setTerminalId(userDevices->at(i).getTerminalId());
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
    }
    if(device_logInfo.getLoginID()!=-1)
    {
        NET_DVR_Logout(device_logInfo.getLoginID());
        device_logInfo.setLoginID(-1);
    }
  //  QImage *img=new QImage();
//    img->load(":/qss/infol");
  //  positionL->setPixmap(QPixmap::fromImage(*img));
//    delete img;

    positionL->show();
}
void CloudWidget::setLabelIma(Substationdata* dat)
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
   infoL->setTerminalId(dat->getTerminalId());
   infoL->setReportTime(dat->getReportTime());
   infoL->setPos(QString::number(dat->getPos()));
   infoL->setSonPos(QString::number(dat->getSonPos()));
   switch (dat->getDatatype()) {
   case 0:
       infoL->setDatatype(CH("����״̬"));
       infoL->setData((dat->getData()==0?CH("��"):CH("��")));
       break;
   case 1:
       infoL->setDatatype(CH("��λ"));
       infoL->setData(QString::number(dat->getData()));
       break;
   case 2:
       infoL->setDatatype(CH("����"));
       infoL->setData(QString::number(dat->getData()));
       break;
   default:
       infoL->setDatatype(CH("����"));
       infoL->setData(QString::number(dat->getData()));
       break;
   }
   infoL->update();
}
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
#define lPlayHandle      lRealPlayHandle
void CloudWidget::cloudCtrUp_press()
{
    PTZControlAll(lPlayHandle,TILT_UP,0,iPTZSpeed);
}

void CloudWidget::cloudCtrDown_press()
{

    PTZControlAll(lPlayHandle,TILT_DOWN,0,iPTZSpeed);
}

void CloudWidget::cloudCtrLeft_press()
{

    PTZControlAll(lPlayHandle,PAN_LEFT,0,iPTZSpeed);
}

void CloudWidget::cloudCtrRight_press()
{

    PTZControlAll(lPlayHandle,PAN_RIGHT,0,iPTZSpeed);
}
void CloudWidget::cloudCtrUp_released()
{

    PTZControlAll(lPlayHandle,TILT_UP,1,iPTZSpeed);
}

void CloudWidget::cloudCtrDown_released()
{

    PTZControlAll(lPlayHandle,TILT_DOWN,1,iPTZSpeed);
}

void CloudWidget::cloudCtrLeft_released()
{
    PTZControlAll(lPlayHandle,PAN_LEFT,1,iPTZSpeed);
}

void CloudWidget::cloudCtrRight_released()
{
    PTZControlAll(lPlayHandle,PAN_RIGHT,1,iPTZSpeed);
}
void CloudWidget::cloudZoomLeft_press()
{
    PTZControlAll(lPlayHandle,ZOOM_IN,0,iPTZSpeed);
}

void CloudWidget::cloudZoomLeft_released()
{
    PTZControlAll(lPlayHandle,ZOOM_IN,1,iPTZSpeed);
}

void CloudWidget::cloudZoomRight_press()
{
    PTZControlAll(lPlayHandle,ZOOM_OUT,0,iPTZSpeed);
}

void CloudWidget::cloudZoomRight_released()
{
    PTZControlAll(lPlayHandle,ZOOM_OUT,1,iPTZSpeed);
}

void CloudWidget::cloudCtrl_auto_press()
{
    PTZControlAll(lPlayHandle,PAN_AUTO,0,iPTZSpeed);
}
void CloudWidget::cloudCtrl_up_left_press()
{
    PTZControlAll(lPlayHandle,UP_LEFT,0,iPTZSpeed);
}
void CloudWidget::cloudCtrl_up_right_press()
{
    PTZControlAll(lPlayHandle,UP_RIGHT,0,iPTZSpeed);
}
void CloudWidget::cloudCtrl_down_left_press()
{
    PTZControlAll(lPlayHandle,DOWN_LEFT,0,iPTZSpeed);
}

void CloudWidget::cloudCtrl_down_right_press()
{
    PTZControlAll(lPlayHandle,DOWN_RIGHT,0,iPTZSpeed);
}
void CloudWidget::cloudCtrl_auto_released()
{
    PTZControlAll(lPlayHandle,PAN_AUTO,1,iPTZSpeed);
}
void CloudWidget::cloudCtrl_up_left_released()
{
    PTZControlAll(lPlayHandle,UP_LEFT,1,iPTZSpeed);
}
void CloudWidget::cloudCtrl_up_right_released()
{
    PTZControlAll(lPlayHandle,UP_RIGHT,1,iPTZSpeed);
}
void CloudWidget::cloudCtrl_down_left_released()
{
    PTZControlAll(lPlayHandle,DOWN_LEFT,1,iPTZSpeed);
}
void CloudWidget::cloudCtrl_down_right_released()
{
    PTZControlAll(lPlayHandle,DOWN_RIGHT,1,iPTZSpeed);
}

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
}
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
            }
            else
            {
                QMessageBox::information(this,CH("��ʾ "),CH(("ץͼʧ��")));
            }
}
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
void  CloudWidget::opencloudClick()
{

  QWidget *current_widget = rightupLayout->currentWidget();
    if(current_widget != cloudVideo)
    {
        if(device_logInfo.getLoginID()==-1)
        {
            QMessageBox::information(this,CH("����"),CH("����������̨"));
            return;
        }
        opencloudw->setText(CH("��ʾ��Ϣ"));
        rightupLayout->setCurrentWidget(cloudVideo);

        hWnd =(HWND)cloudL->winId() ;
        if(isNormalCarmer)
        {
          QMessageBox::information(this,"AA",CH("��ͨ"));
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
         if (lRealPlayHandle < 0)
          {
                QMessageBox::information(this,CH("����"),CH("��̨����ʧ��,�������:")+QString::number(NET_DVR_GetLastError()));
                return;
          }
        }
        else
        {


        }
         setButtonstatus(true);
    }
    else
    {

        if(lRealPlayHandle!=-1)
        {
                NET_DVR_StopRealPlay(lRealPlayHandle);
                lRealPlayHandle=-1;
                setButtonstatus(false);
#ifdef   SDK_REALPLAY
                PlayM4_Stop(lPort);
                PlayM4_CloseStream(lPort);
                PlayM4_FreePort(lPort);
#endif
        }
       opencloudw->setText(CH("��ʾ��Ƶ"));
       rightupLayout->setCurrentWidget(infoWid);
    }
}

void CloudWidget::normal_infra_slot(int id)
{

    if(id==0)
    {
        isNormalCarmer=true;
    }
    else
    {
        isNormalCarmer=false;
    }
}
