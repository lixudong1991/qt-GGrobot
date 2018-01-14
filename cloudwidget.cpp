#include"cloudwidget.h"
#include <string.h>
#include <QDir>
#include <QEvent>
#include <QHelpEvent>
#include <QToolTip>

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
    dir.setPath("map");
    if(!dir.exists())
    {
        dir.mkpath("map");
    }

    NET_DVR_Init();
    NET_DVR_SetConnectTime(2000, 1);
    NET_DVR_SetReconnect(10000, true);
    NetDev_Init();   ////初始化sdk
    if(!SHOWIMAGE_Init())
     {
          LOGE("SHOWIMAGE_Init() error");
     }//灰图显示sdk初始化
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
   NetDev_Cleanup();  //释放SDK资源

   if(m_sShowPort!=-1)
   {
       SHOWIMAGE_FreePort(m_sShowPort);
   }

   SHOWIMAGE_Cleanup();
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

    leftla->addLayout(leftupLayout,0,0);  //左上


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

    leftla->addLayout( leftdownLayout,1,0);  //左下


    QVBoxLayout *infoLay=new QVBoxLayout();
    infoLay->addWidget(infoL);
    infoLay->setContentsMargins(0,0,0,0);

    leftla->addLayout(infoLay,0,1);   //右上

    QVBoxLayout *rightdownla=new QVBoxLayout();
    rightdownla->addWidget(positionL);
    rightdownla->setContentsMargins(0,0,0,0);
    leftla->addLayout(rightdownla,1,1);  //右下

    leftla->setContentsMargins(0,0,0,0);

    devices_log=new QGroupBox(CH("设备"));
    nonnectCloud=new QGroupBox(CH("云台"));
    right_cloudCtrl=new QGroupBox(CH("云台控制"));
    right_patrolView=new QGroupBox(CH("自动巡检"));

    int wid=w*0.132-10;

    devices_log->setFixedSize(wid,wid*0.382);
    nonnectCloud->setFixedSize(wid,wid*0.382);
    right_cloudCtrl->setFixedSize(wid,wid*1.911);
    right_patrolView->setFixedSize(wid,wid*0.641);

    rightla->addWidget(devices_log);
    rightla->addWidget(right_patrolView);
    rightla->addWidget(nonnectCloud);
    rightla->addWidget(right_cloudCtrl);

    QHBoxLayout *device=new QHBoxLayout();
    device->addWidget(new QLabel(CH("设备ID:")));
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
        rightcloud->addWidget(new QLabel(CH("云台速度:")),5,0,1,2);
        rightcloud->addWidget(cloudSpeed,5,2,1,1);
        rightcloud->addWidget(new QLabel(CH("焦距: ")),6,0,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalLeft,6,1,1,1);
        rightcloud->addWidget(cloudnormalCamera_focalRight,6,2,1,1);
        rightcloud->addWidget(new QLabel(CH("红外焦距: ")),7,0,1,2);
        rightcloud->addWidget(infradautoFocus,7,2,1,1);
        right_cloudCtrl->setLayout(rightcloud);



    QVBoxLayout *rightpatrolView=new QVBoxLayout();
    rightpatrolView->addWidget(inspecting_Start_Stop);
    rightpatrolView->addWidget(inspecting_Pause_Continue);
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

//    nor=new QRadioButton(CH("普通"));
//    nor->setChecked(true);
//    infra=new QRadioButton(CH("红外"));
//    normal_infra=new QButtonGroup();
//    normal_infra->addButton(nor,0);
//    normal_infra->addButton(infra,1);




    cloudnormalCamera_focalLeft=new QPushButton(CH("伸"));
    cloudnormalCamera_focalRight=new QPushButton(CH("缩"));
    infradautoFocus=new QPushButton(CH("自动"));

     inspecting_Start_Stop=new QPushButton(CH("开始巡检"));
     inspecting_Start_Stop->setEnabled(false);
     inspecting_Pause_Continue=new QPushButton(CH("暂停巡检"));;
     inspecting_Pause_Continue->setEnabled(false);

    slotsinit();
    setButtonstatus(false);

}
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

 }

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
void CloudWidget::log_bt_slot()
{
        if(device_logInfo.getLoginID()!=-1)
        {
            return;
        }

        BOOL ret = SHOWIMAGE_GetPort(&m_sShowPort);
        if(ret == FALSE)
        {
                QMessageBox::critical(this,CH("错误"),CH("获取红外图象显示端口失败"));
                return;
        }

        SHOWIMAGE_SetShowImageWnd(m_sShowPort,(HWND)infraredL->winId());


        QString ip=term->getCloudIp();
        QString port=term->getCloudPort();
        QString user=term->getCloudUser();
        QString pwd=term->getCloudPwd();

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
        memset(&m_RawHead,0,sizeof(m_RawHead));
        QMessageBox::information(this,CH("提示 "),CH("连接成功:")+QString::number(loginid));
}


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
        connect(&sportT,SIGNAL(execComStatus(int)),this,SLOT(setInspectingStatus(int)));
        sportT.start();
        infoL->show();


        log_bt->setEnabled(true);
        opencloudw->setEnabled(true);
        inspecting_Start_Stop->setEnabled(true);
        inspecting_Pause_Continue->setEnabled(true);
}

void CloudWidget::querError()
{
    QMessageBox::information(this,CH("错误"),CH("网络异常"));
    exit(0);
}

void CloudWidget::deviceidChange(int i)
{
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
    int width=w*0.868;
    positionL->setBackImg((width-16)/2,h/2-12,userDevices->at(i).getTerminalId());
}
void CloudWidget::setLabelIma(Substationdata* dat,QList<int>*is)
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
       infoL->setData(QString::number(dat->getData()*0.01));
       break;
   default:
       infoL->setDatatype(CH("其它"));
       infoL->setData(QString::number(dat->getData()));
       break;
   }
   infoL->update();
   positionL->startPoint(dat->getPos(),is);
   LOGI("startPoint:"<<dat->getPos());
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
    infradautoFocus_click();
}

void CloudWidget::cloudCtrDown_released()
{

    PTZControlAll(lPlayHandle,TILT_DOWN,1,iPTZSpeed);
    infradautoFocus_click();
}

void CloudWidget::cloudCtrLeft_released()
{
    PTZControlAll(lPlayHandle,PAN_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}

void CloudWidget::cloudCtrRight_released()
{
    PTZControlAll(lPlayHandle,PAN_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
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
    infradautoFocus_click();
}
void CloudWidget::cloudCtrl_up_left_released()
{
    PTZControlAll(lPlayHandle,UP_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}
void CloudWidget::cloudCtrl_up_right_released()
{
    PTZControlAll(lPlayHandle,UP_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
}
void CloudWidget::cloudCtrl_down_left_released()
{
    PTZControlAll(lPlayHandle,DOWN_LEFT,1,iPTZSpeed);
    infradautoFocus_click();
}
void CloudWidget::cloudCtrl_down_right_released()
{
    PTZControlAll(lPlayHandle,DOWN_RIGHT,1,iPTZSpeed);
    infradautoFocus_click();
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
    infradautoFocus->setEnabled(b);
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

  QWidget *current_widget = leftupLayout->currentWidget();
    if(current_widget != cloudVideo)
    {
        if(device_logInfo.getLoginID()==-1)
        {
            QMessageBox::information(this,CH("错误"),CH("请先连接云台"));
            return;
        }
        hWnd =(HWND)cloudL->winId() ;
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
         if (lRealPlayHandle< 0)
          {
                QMessageBox::information(this,CH("错误"),CH("播放失败"));
                return;
          }
         opencloudw->setText(CH("显示信息"));
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
       opencloudw->setText(CH("显示视频"));
       leftupLayout->setCurrentWidget(normalWid);
       leftdownLayout->setCurrentWidget(infraredWid);
    }
}
void CALLBACK funRealStream(DWORD dwDataType, char* pDataBuffer, DWORD dwDataSize,DWORD dwUser, short)
{
    CloudWidget* pThis = (CloudWidget*)dwUser;
    if(pThis == NULL) return;
    pThis->PushRealData(dwDataType,pDataBuffer,dwDataSize);
}

bool CloudWidget::startGray()//start get continue gray data
{
    if(m_sRealHandle != -1)
    {
        return false;
    }
    //连接设备
    QString grayIp=term->getInfraredIp();
    m_sRealHandle = NetDev_Connect(const_cast<char*>(grayIp.toStdString().c_str()),CONNECT_TYPE_ULIRNET);   //
    if(m_sRealHandle == -1)
    {
        //QMessageBox::information(this,CH("错误"),CH("连接失败"));
        return false;
    }
    //开始获取实时数据  ,TI35、TI65系列设备
    BOOL ret = NetDev_StartRealStream(m_sRealHandle,STREAM_TYPE_GRAYDATA);
    if(ret == FALSE)
    {
    //    QMessageBox::information(this,CH("错误"),CH("开始获取视频失败"));
        return false;
    }
    //设置实时数据回调  TI35、TI65系列设备
    NetDev_SetRealStreamCallBack(m_sRealHandle,funRealStream,(DWORD)this);
    return true;
}

void CloudWidget::stopGray()//stop get gray data
{
    // TODO: 在此添加控件通知处理程序代码
    //停止获取实时数据  TI35、TI65系列设备
    NetDev_StopRealStream(m_sRealHandle);
    //断开连接
    NetDev_DisConnect(m_sRealHandle);
    m_sRealHandle = -1;
    memset(&m_RawHead,0,sizeof(m_RawHead));
}
void CloudWidget::PushRealData(DWORD dwDataType,char *pDataBuffer,DWORD dwDataSize)
{
//	g_dwCount ++;
//	MYTRACE("HXY:获取总帧数：%d",g_dwCount);
    switch(dwDataType)
    {
    case AVI_HEAD:
    case AVI_DATA:
        break;
    case GRAY_HEAD://保存数据头
        if(sizeof(m_RawHead) == dwDataSize)
        {
            memcpy(&m_RawHead,pDataBuffer,dwDataSize);
            SHOWIMAGE_SetImageSize(m_sShowPort,m_RawHead.nDectorImageW,m_RawHead.nDectorImageH);
        }
        break;
    case GRAY_DATA://解析数据并显示

        if(Temperature_GetFrameInfo(m_RawHead.nCalcType,(byte*)pDataBuffer,dwDataSize,&m_pData,&m_dwDataSize,&m_pFrameHead,&m_dwHeadSize) == TRUE)
        {
            SHOWIMAGE_ShowImage(m_sShowPort, m_pData, m_dwDataSize, 100, 0);
            //重新计算温度
            CalculateCurSor();
            SetMessage();
        }
        break;
    default:
        break;
    }
}
 void CloudWidget::infradautoFocus_click()
 {
     if(m_sRealHandle!=-1)
     {
         NetDev_DoAction((short)m_sRealHandle, ULIR_KEY_AUTO_FOCUS);
     }
 }

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
    m_fCursorTemp = Temperature_GetTempFromGray(pTemp[ptnew.x+m_RawHead.nDectorImageW*ptnew.y],0.96,(byte*)m_pFrameHead,m_dwHeadSize,m_RawHead.nCalcType);
}
void CloudWidget::SetMessage()
{
    QString  strShowInfo= "<ultemp><CURSOR>";
    strShowInfo+=QString::number(m_pCursorPoint.x);
    strShowInfo+=",";
    strShowInfo+=QString::number(m_pCursorPoint.y);
    strShowInfo+=",";
    strShowInfo+=QString::number(m_fCursorTemp);
    strShowInfo+= "</CURSOR><ultemp>";

    //考虑加入鼠标的温度
    SHOWIMAGE_SetObjectMessage(m_sShowPort,const_cast<char*>(strShowInfo.toStdString().c_str()));
//    NET_DEV_FULLRECTPARAM fullTemp;
//    memset(&fullTemp,0,sizeof(NET_DEV_FULLRECTPARAM));
//    DWORD re;
//    if(NetDev_GetConfig(m_sRealHandle,ULIR_MEASURE_GET_MAXTEMP2,(void*)&fullTemp,sizeof(NET_DEV_FULLRECTPARAM),&re))
//    {
//        m_fullMaxTemp=fullTemp.nMaxtTemp100*0.01;
//        m_fullMinTemp=fullTemp.nMinTemp100*0.01;
//    }
}
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
                LOGI("抓图成功:"<< qApp->applicationDirPath().toStdString().c_str()<<"/"<<file.toStdString().c_str());
            }
            else
            {
                 QMessageBox::information(this,CH("提示 "),CH(("抓图失败")));
                  LOGE("抓图失败");
            }
  //          char buff[640*480*4] ;
//            memset(buff,0,sizeof(buff));
 //           DWORD size=0;
//            if(m_sRealHandle!=-1)
//            {
//                LOGI("红相开始抓图");
//                if(NetDev_CaptureJPEGPicture(m_sRealHandle,buff,sizeof(buff) , &size)==0)
//                {
//                     QMessageBox::information(this,CH("提示 "),CH("红相抓图失败"));
//                     return;
//                }
//                LOGI("红相抓图成功: "<<size);
//            }
}
 void CloudWidget::setInspectingStatus(int status)
 {
     inspecting_Pause_Continue->setEnabled(true);
     inspecting_Start_Stop->setEnabled(true);
     if(status==0)
     {
         if(sportid==0)
         {
                if(cmdStart_Stop==0)
                {
                    cmdStart_Stop=1;
                    inspecting_Start_Stop->setText(CH("停止巡检"));
                }else
                {
                    cmdStart_Stop=0;
                    inspecting_Start_Stop->setText(CH("开始巡检"));
                }
         }else{
             if(cmdPause_Continue==0)
             {
                 cmdPause_Continue=1;
                 inspecting_Pause_Continue->setText(CH("继续巡检"));
             }else
             {
                  cmdPause_Continue=0;
                  inspecting_Pause_Continue->setText(CH("暂停巡检"));
             }
         }
     }else
     {
         QMessageBox::information(this,CH("提示 "),CH("发送命令失败"));
     }
 }

void CloudWidget::inspecting_Start_StopClick()
{
    if(sportT.isRunning())
    {
        sportid=0;
        inspecting_Pause_Continue->setEnabled(false);
        inspecting_Start_Stop->setEnabled(false);
        if(cmdStart_Stop==0)
        {

            sportT.iceSendCommand(QString(STATUS_STARTAUTO));
        }
        else
        {
            sportT.iceSendCommand(QString(STATUS_QUICKBACK));
        }
    }
}

void CloudWidget::inspecting_Pause_ContinueClick()
{  
    if(sportT.isRunning())
    {
        sportid=1;
        inspecting_Pause_Continue->setEnabled(false);
        inspecting_Start_Stop->setEnabled(false);
        if(cmdStart_Stop==0)
        {
            sportT.iceSendCommand(QString(STATUS_PAUSEAUTO));
        }else
        {
           // sportT.iceSendCommand(QString(STATUS_CONTINUEAUTO));
            sportT.iceSendCommand(QString(STATUS_PAUSEAUTO));
        }
    }
}

