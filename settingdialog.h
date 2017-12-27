#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include "head.h"
#include "dialog.h"
#include "push_button.h"
#include "msg_box.h"
class SettingDialog : public Dialog
{
    Q_OBJECT

public:

    explicit SettingDialog(QWidget *parent = 0);
    ~SettingDialog();
protected:
    void paintEvent(QPaintEvent *event);
private slots:
    void dbsave();
private:
    QLabel *dbserver_label;
    QLabel *dbport_label;
    QLabel *dbuser_label;
    QLabel *dbpwd_label;
    QLabel *db_label;

    QLineEdit *dbserverip;
    QLineEdit *dbport;
    QLineEdit *dbuser;
    QLineEdit *dbpwd;
    QLineEdit *db;


    QLabel *ftpserver_label;
    QLabel *ftpport_label;
    QLabel *ftpuser_label;
    QLabel *ftppwd_label;

    QLineEdit *ftpserverip;
    QLineEdit *ftpport;
    QLineEdit *ftpuser;
    QLineEdit *ftppwd;

    QLabel *pictimeConfigL;
    QLineEdit *pictimeConfig;

    QPushButton *setbt;
    PushButton *closebt;

    QWidget *title;
    QWidget *dbconfig;
    QWidget *ftpconfig;
    QWidget *picTimeW;
    QTabWidget *center;
    MsgBox *box=new MsgBox();
};

#endif // SETTINGDIALOG_H
