#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include "head.h"
#include "dialog.h"
#include "cloudwidget.h"
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

    void setUserDevice(QList<Userterminal> *);
    void doLog();
signals:
        void exitMain();
        void netErr();
        void showMin();
public slots:

private slots:

    void showMainMenu();

    void showSettingDialog();

    void showLoginDialog();

    void showdbManage();
 //   void showImportAlarm();
	void turnPage(int current_page);

    void setAlarmstatus(int);
    void resetAlarmstatus();
    void neterror();

private:

	QStackedWidget *statked_widget;

	TitleWidget *title_widget; //标题栏

    CloudWidget *Cloud_widget; //主界面内容

    ExportWidget *exprot_widget;//导出报表界面
    AlarmWidget  *alarmwidget;

    MainMenu *main_menu; //主菜单
};

#endif // MAINWIDGET_H
