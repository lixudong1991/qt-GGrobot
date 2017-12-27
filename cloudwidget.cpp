#include"cloudwidget.h"
#include <string.h>
#include <QDir>

//#define SDK_REALPLAY

#ifdef  SDK_REALPLAY
#include "HCNetSdk/plaympeg4.h"
#define RESOLUTION  480*270
LONG lPort; //全局的播放库port号
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
    leftla->addLayout(leftupla,0,0);  //左上



    QVBoxLayout *infraredla=new QVBoxLayout();
    infraredla->addWidget(infraredImageL);
     infraredla->setContentsMargins(0,0,0,0);
    leftla->addLayout(infraredla,1,0);  //左下

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

   leftla->addLayout(rightupLayout,0,1);   //右上

    QVBoxLayout *rightdownla=new QVBoxLayout();
    rightdownla->addWidget(positionL);
     rightdownla->setContentsMargins(0,0,0,0);
    leftla->addLayout(rightdownla,1,1);  //右下

    leftla->setContentsMargins(0,0,0,0);

    devices_log=new QGroupBox(CH("设备"));
    nonnectCloud=new QGroupBox(CH("云台和工控机"));
    right_cloudCtrl=new QGroupBox(CH("云台控制"));
    right_patrolView=new QGroupBox(CH("巡检"));

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
    device->addWidget(new QLabel(CH("设备名称:")));
    device->addWidget(deviceid);
    devices_log->setLayout(device);

    QHBoxLayout *concloud=new QHBoxLayout();
    concloud->addWidget(log_bt);
    nonnectCloud->setLayout(concloud);

    QGridLayout *rightcloud=new QGridLayout();
        rightcloud->addWidget(new QLabel(CH("摄像头:")), 0, 0, 1, 1);
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
        rightcloud->addWidget(new QLabel(CH("云台速度:")),6,0,1,2);
        rightcloud->addWidget(cloudSpeed,6,2,1,1);
        rightcloud->addWidget(new QLabel(CH("焦距: ")),7,0,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalLeft,7,1,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalRight,7,2,1,1);
    right_cloudCtrl->setLayout(rightcloud);



    QVBoxLayout *rightpatrolView=new QVBoxLayout();
    rightpatrolView->addWidget(patrolView_Start);
    right_patrolView->setLayout(rightpatrolView);

}
void CloudWidget::right_groupinit()
{

    log_bt=new QPushButton(CH("连接"));
    log_bt->setEnabled(false);
    deviceid=new QComboBox();
    opencloudw=new QPushButton(CH("显示视频"));
    opencloudw->setEnabled(false);


    cloudCtrl_up=new QPushButton(CH("上"));
    cloudCtrl_down=new QPushButton(CH("下"));
    cloudCtrl_left=new QPushButton(CH("左"));
    cloudCtrl_auto=new QPushButton(CH("自动"));
    cloudCtrl_right=new QPushButton(CH("右"));  
    cloudCtrl_up_left=new QPushButton(CH("左上"));
    cloudCtrl_up_right=new QPushButton(CH("右上"));
    cloudCtrl_down_left=new QPushButton(CH("左下"));
    cloudCtrl_down_right=new QPushButton(CH("右下"));
    cloudCapture=new QPushButton(CH("抓图"));
    cloudWiperPwron=new QPushButton(CH("开雨刷"));
    cloudRecord=new QPushButton(CH("录像"));


    cloudSpeed=new QComboBox();
    for(int i=1;i<8;i++)
    {
        cloudSpeed->addItem(QString::number(i));
    }

    nor=new QRadioButton(CH("普通"));
    infra=new QRadioButton(CH("红外"));
    normal_infra=new QButtonGroup();
    normal_infra->addButton(nor,0);
    normal_infra->addButton(infra,1);



    cloudnormalCamera_focalLeft=new QPushButton(CH("伸"));
    //cloudnormalCamera_focalLeft->setIconSize(pixmap.size());

    cloudnormalCamera_focalRight=new QPushButton(CH("缩"));

    patrolView_Start=new QPushButton(CH("取消巡检"));

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

        struLoginInfo.bUseAsynLogin = 0; //同步登录方式
        strcpy(struLoginInfo.sDeviceAddress, ip.toStdString().c_str()); //设备IP地址
        struLoginInfo.wPort = port.toInt(); //设备服务端口
        strcpy(struLoginInfo.sUserName, user.toStdString().c_str()); //设备登录用户名
        strcpy(struLoginInfo.sPassword, pwd.toStdString().c_str()); //设备登录密码

        NET_DVR_DEVICEINFO_V40 struDeviceInfoV40 = {0};

        long loginid=NET_DVR_Login_V40(&struLoginInfo, &struDeviceInfoV40);
        device_logInfo.setLoginID(loginid);
        if (loginid < 0)
        {
               QMessageBox::critical(this,CH("错误"),CH("连接云台失败, 错误代码: ")+QString::number(NET_DVR_GetLastError()));
               return;
        }

        NET_DVR_IPPARACFG_V40 IpAccessCfg;
        memset(&IpAccessCfg,0,sizeof(IpAccessCfg));
        DWORD  dwReturned;

        NET_DVR_GetDVRConfig(device_logInfo.getLoginID(),NET_DVR_GET_IPPARACFG_V40,0,&IpAccessCfg,sizeof(NET_DVR_IPPARACFG_V40),&dwReturned);
        DwStartDChan=IpAccessCfg.dwStartDChan;


      QMessageBox::information(this,CH("提示 "),CH("连接成功:")+QString::number(loginid));
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
    QMessageBox::information(this,CH("错误"),CH("网络异常"));
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
       infoL->setDatatype(CH("开关状态"));
       infoL->setData((dat->getData()==0?CH("关"):CH("开")));
       break;
   case 1:
       infoL->setDatatype(CH("油位"));
       infoL->setData(QString::number(dat->getData()));
       break;
   case 2:
       infoL->setDatatype(CH("红外"));
       infoL->setData(QString::number(dat->getData()));
       break;
   default:
       infoL->setDatatype(CH("其它"));
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
                QMessageBox::information(this,CH("提示 "),CH("云台控制失败!"));
                return;
            }
        }
        else
        {
            ret = NET_DVR_PTZControl(lRealHandle,dwPTZCommand,dwStop);
            if(!ret)
            {
                QMessageBox::information(this,CH("提示 "),CH("云台控制失败!"));
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
            //组建jpg结构
            NET_DVR_JPEGPARA JpgPara = {0};
            JpgPara.wPicSize =0;
            JpgPara.wPicQuality = 0;
            if(NET_DVR_CaptureJPEGPicture(device_logInfo.getLoginID(), DwStartDChan+1, &JpgPara, const_cast<char *>(file.toStdString().c_str())))
            {
                 QMessageBox::information(this,CH("提示 "),CH(("抓图成功,文件保存在:"))+qApp->applicationDirPath()+"/"+SAVEPICTURE);
            }
            else
            {
                QMessageBox::information(this,CH("提示 "),CH(("抓图失败")));
            }
}
void  CloudWidget::cloudWiperPwron_click()
{
        static bool v=true;
        if(v)
        {
            cloudWiperPwron->setText(CH("关雨刷"));
            NET_DVR_PTZControl(lRealPlayHandle,WIPER_PWRON,0);
        }
        else
        {
            cloudWiperPwron->setText(CH("开雨刷"));
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
            QMessageBox::information(this,CH("提示 "),CH(("启动录像失败")));
            return;
        }
          cloudRecord->setText(CH("停止"));
    }
    else
    {
          if(!NET_DVR_StopSaveRealData(lRealPlayHandle))
          {
              QMessageBox::information(this,CH("提示 "),CH(("停止录像失败")));
              return;
          }
         cloudRecord->setText(CH("启动"));
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
    case NET_DVR_SYSHEAD: //系统头
        if (!PlayM4_GetPort(&lPort))  //获取播放库未使用的通道号
        {
            break;
        }
        //m_iPort = lPort; //第一次回调的是系统头，将获取的播放库port号赋值给全局port，下次回调数据时即使用此port号播放
        if (dwBufSize > 0)
        {
            if (!PlayM4_SetStreamOpenMode(lPort, STREAME_REALTIME))  //设置实时流播放模式
            {
                break;
            }

            if (!PlayM4_OpenStream(lPort, pBuffer, dwBufSize,RESOLUTION)) //打开流接口
            {
                break;
            }
            if (!PlayM4_Play(lPort, hWnd)) //播放开始
            {
                break;
            }
        }
        break;
    case NET_DVR_STREAMDATA:   //码流数据
        if (dwBufSize > 0 && lPort != -1)
        {
            if (!PlayM4_InputData(lPort, pBuffer, dwBufSize))
            {
                break;
            }
        }
        break;
    default: //其他数据
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
            QMessageBox::information(this,CH("错误"),CH("请先连接云台"));
            return;
        }
        opencloudw->setText(CH("显示信息"));
        rightupLayout->setCurrentWidget(cloudVideo);

        hWnd =(HWND)cloudL->winId() ;
        if(isNormalCarmer)
        {
          QMessageBox::information(this,"AA",CH("普通"));
            //获取窗口句柄
         NET_DVR_PREVIEWINFO struPlayInfo = {0};
         struPlayInfo.lChannel= DwStartDChan+1 ;       //预览通道号
         struPlayInfo.dwStreamType = 0;       //0-主码流，1-子码流，2-码流3，3-码流4，以此类推
         struPlayInfo.dwLinkMode   = 0;       //0- TCP方式，1- UDP方式，2- 多播方式，3- RTP方式，4-RTP/RTSP，5-RSTP/HTTP
#ifdef  SDK_REALPLAY
         struPlayInfo.hPlayWnd = NULL;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
         lRealPlayHandle = NET_DVR_RealPlay_V40(device_logInfo.getLoginID(), &struPlayInfo,g_RealDataCallBack_V30, NULL);
#else
         struPlayInfo.hPlayWnd = hWnd;         //需要SDK解码时句柄设为有效值，仅取流不解码时可设为空
         lRealPlayHandle = NET_DVR_RealPlay_V40(device_logInfo.getLoginID(), &struPlayInfo,NULL, NULL);
#endif
         if (lRealPlayHandle < 0)
          {
                QMessageBox::information(this,CH("错误"),CH("云台播放失败,错误代码:")+QString::number(NET_DVR_GetLastError()));
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
       opencloudw->setText(CH("显示视频"));
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
