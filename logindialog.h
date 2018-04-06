#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H
#include "head.h"
#include <QCloseEvent>
#include "dialog.h"
#include "push_button.h"
#include "loading_widget.h"
#include "loginthread.h"
#include "userterminal.h"
class LoginDialog : public QDialog
{
    Q_OBJECT

public:

    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
   void translateLanguage();
    bool createDbConnect();
    void setTreadDevices(QList<Userterminal> *devics)
    {
        logt.setDevicesList(devics);
    }

    void reLogin();

signals:
   void doLogin(int);
   void exitMain();
   void showdbset();
protected:
    void paintEvent(QPaintEvent *);
    void initloginwid();
    void inittitlewid();
    void closeEvent(QCloseEvent *);
private slots:
    void verify();
    void logstatus(int);

private:

    QStackedLayout *login_stacked_layout;

    PushButton *close_button;
    QLabel *title_label;

    QLineEdit *password_line_edit;  
    QCheckBox *remember_check_box;
    QLineEdit *account_combo_box;

    QListWidget *list_widget;

    QPushButton *login_button;
    QPushButton *configbt;

    QWidget *login_widget;
    QWidget *title_wid;
    LoadingWidget *loading_widget;


    QWidget *logmsg;
    QLabel *msg;

    LoginThread logt;
    bool islog=false;
    QString username;
    QString password;
};
#endif
