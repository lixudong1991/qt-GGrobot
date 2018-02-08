#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "head.h"
#include "dialog.h"
#include "cloudwidget.h"
#include "logindialog.h"
#include "titlewidget.h"
#include "settingdialog.h"
#include "mainmenu.h"
#include "exportwidget.h"
#include "alarmwidget.h"
#include "userterminal.h"
class MainWidget : public QDialog
{
    Q_OBJECT
public:

    MainWidget(QWidget *parent = 0);
    ~MainWidget();


protected:
       void mousePressEvent(QMouseEvent *event);
        void mouseReleaseEvent(QMouseEvent *event);
        void mouseMoveEvent(QMouseEvent *event);
public slots:


private slots:

    void showMainMenu();

    void showSettingDialog();

    void showLoginDialog();

    void showdbManage();
 //   void showImportAlarm();
	void turnPage(int current_page);

    void doLog();

    void setAlarmstatus(int);
    void resetAlarmstatus();


private:
    QPoint move_point;
    bool mouse_press;
	QStackedWidget *statked_widget;

	TitleWidget *title_widget; //标题栏

    CloudWidget *Cloud_widget; //主界面内容

    ExportWidget *exprot_widget;//导出报表界面
    AlarmWidget  *alarmwidget;

    LoginDialog *login_dialog; //登录界面

    MainMenu *main_menu; //主菜单

   QList<Userterminal> *userDevices;


};

#endif // MAINWIDGET_H
