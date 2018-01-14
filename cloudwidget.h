#ifndef CLOUDWIDGET_H
#define CLOUDWIDGET_H
#include "head.h"
#include "userterminal.h"
#include "thread.h"
#include "login_device_info.h"
#include "substationdata.h"
#include "infowidget.h"
#include "routewidget.h"
#include "HCNetSdk/HCNetSDK.h"
#include "HCNetSdk/IShowImage.h"
#include "HCNetSdk/IUlirTemperatureSDK.h"
#include "HCNetSdk/IUlirNetDevSDK.h"
#include "sportsctrthread.h"
class CloudWidget : public QWidget
{
    Q_OBJECT
public:

    explicit CloudWidget(QWidget *parent = 0);
    ~CloudWidget();
    void setUserDevices(const QList<Userterminal> *devices)
    {
        userDevices=devices;
    }
    void initTerminal();
    void setLabelSize(int wid,int hei);


     void PushRealData(DWORD dwDataType,char *pDataBuffer,DWORD dwDataSize);
public slots:
    void log_bt_slot();
    void opencloudClick();
    void deviceidChange(int);
    void setLabelIma(Substationdata*,QList<int>*);
    void querError();

    void cloudCtrUp_press();
    void cloudCtrDown_press();
    void cloudCtrLeft_press();
    void cloudCtrRight_press();
    void cloudCtrl_auto_press();
    void cloudCtrl_up_left_press();
    void cloudCtrl_up_right_press();
    void cloudCtrl_down_left_press();
    void cloudCtrl_down_right_press();


    void cloudCtrUp_released();
    void cloudCtrDown_released();
    void cloudCtrLeft_released();
    void cloudCtrRight_released();
    void cloudCtrl_auto_released();
    void cloudCtrl_up_left_released();
    void cloudCtrl_up_right_released();
    void cloudCtrl_down_left_released();
    void cloudCtrl_down_right_released();


    void cloudCapture_click();
    void cloudWiperPwron_click();
    void cloudRecord_click();

    void cloudSpeed_Change(int);

    void cloudZoomLeft_press();
    void cloudZoomLeft_released();
    void cloudZoomRight_press();
    void cloudZoomRight_released();

    void infradautoFocus_click();

    void inspecting_Start_StopClick();
    void inspecting_Pause_ContinueClick();

    void setInspectingStatus(int);
protected:
     void paintEvent(QPaintEvent *event);
     bool event(QEvent *et);
signals:


private:

    QStackedLayout *leftupLayout;
    QWidget *cloudVideo;
    QLabel *cloudL;
    QWidget *normalWid;
    QLabel *normalImageL;

    QStackedLayout *leftdownLayout;
    QWidget *infraredVideo;
    QLabel *infraredL;
    QWidget *infraredWid;
    QLabel *infraredImageL;

    RouteWidget *positionL;

    Infowidget *infoL;


    QPushButton *opencloudw;

    QPushButton *cloudCtrl_up;
    QPushButton *cloudCtrl_down;
    QPushButton *cloudCtrl_left;
    QPushButton *cloudCtrl_right;

    QPushButton *cloudCtrl_auto;

    QPushButton *cloudCtrl_up_left;
    QPushButton *cloudCtrl_up_right;
    QPushButton *cloudCtrl_down_left;
    QPushButton *cloudCtrl_down_right;

    QPushButton *cloudCapture;
    QPushButton *cloudWiperPwron;
    QPushButton *cloudRecord;


    QComboBox *cloudSpeed;

    QPushButton *cloudnormalCamera_focalLeft;
    QPushButton *cloudnormalCamera_focalRight;
    QPushButton *infradautoFocus;

    QPushButton *inspecting_Start_Stop;
    QPushButton *inspecting_Pause_Continue;

    QPushButton *log_bt;
    QComboBox *deviceid;


    QGroupBox *devices_log;
    QGroupBox *nonnectCloud;
    QGroupBox *right_cloudCtrl;
    QGroupBox *right_patrolView;

    void labelinit();

    void right_groupinit();
    void posinit();

    void slotsinit();



    const QList<Userterminal> *userDevices;
    const Userterminal *term;
    Thread t;

    Login_device_info device_logInfo;
    LONG lRealPlayHandle=-1;

    void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);
    void setButtonstatus(bool b);
    int DwStartDChan=-1;
    int iPTZSpeed=1;


    int w;
    int h;


    short m_sShowPort=-1;
    short m_sRealHandle=-1;
    NET_DEV_RAWFILEHEAD m_RawHead;
    BYTE * m_pData ;
    DWORD m_dwDataSize ;
    BYTE * m_pFrameHead ;
    DWORD m_dwHeadSize;
    float m_fCursorTemp;
    float m_fullMaxTemp;
    float m_fullMinTemp;

    int PLAYVIDEODLG_WIDTH=0;
    int PLAYVIDEODLG_HIGH=0;
    int px, py,px1,py1;
    POINT m_pCursorPoint;

    bool startGray();//start get continue gray data
    void stopGray();//start get continue gray data
    void CalculateCurSor();
    void SetMessage();

    SportsCtrThread sportT;
    int sportid=0;
    int cmdStart_Stop=0;
    int cmdPause_Continue=0;
};

#endif // CLOUDWIDGET_H
