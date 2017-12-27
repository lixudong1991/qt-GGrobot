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
    void paintEvent(QPaintEvent *event);
public slots:
    void log_bt_slot();
    void opencloudClick();
    void normal_infra_slot(int);
    void deviceidChange(int);
    void setLabelIma(Substationdata*);
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
protected:


signals:


private:
    QLabel *normalImageL;
    QLabel *infraredImageL;
    RouteWidget *positionL;
   //  QLabel *positionL;

    QStackedLayout *rightupLayout;
    QWidget *cloudVideo;
    QWidget *infoWid;
    Infowidget *infoL;
    QLabel *cloudL;

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
    QRadioButton *nor;
    QRadioButton *infra;  
    QButtonGroup *normal_infra;




    QPushButton *cloudnormalCamera_focalLeft;
    QPushButton *cloudnormalCamera_focalRight;

    QPushButton *patrolView_Start;


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
    Thread t;

    Login_device_info device_logInfo;
    LONG lRealPlayHandle=-1;

    void PTZControlAll(LONG lRealHandle, DWORD dwPTZCommand, DWORD dwStop, int Speed);
    void setButtonstatus(bool b);
    int DwStartDChan=-1;
    int iPTZSpeed=1;

    bool isNormalCarmer=true;


    int w;
    int h;
};

#endif // CLOUDWIDGET_H
