#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "head.h"
#include "dialog.h"
#include "push_button.h"
#include "loading_widget.h"
#include "loginthread.h"
#include "userterminal.h"
class LoginDialog : public Dialog
{
    Q_OBJECT

public:

    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
   void translateLanguage();
    bool createDbConnect();
    void closeEvent(QCloseEvent*);
    void setTreadDevices(QList<Userterminal> *devics)
    {
        logt.setDevicesList(devics);
    }

signals:
   void doLogin();
protected:

    void initloginwid();
    void inittitlewid();
private slots:
    void verify();
    void logstatus(int);
private:

    QStackedLayout *login_stacked_layout;

    PushButton *close_button;
    QLabel *title_label;

    QLabel *account_label;
    QLabel *password_label;

    QLineEdit *password_line_edit;  
    QCheckBox *remember_check_box;
    QCheckBox *auto_login_check_box;
    QComboBox *account_combo_box;

    QListWidget *list_widget;

    QPushButton *login_button;

    QWidget *login_widget;
    QWidget *title_wid;
    LoadingWidget *loading_widget;

    QWidget *logmsg;
    QLabel *msg;

    LoginThread logt;
    bool islog=false;
};
#endif
