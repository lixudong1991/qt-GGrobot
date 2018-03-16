#ifndef ALARMWIDGET_H
#define ALARMWIDGET_H

#include"head.h"
#include <QDateTimeEdit>
#include <QTableWidget>
#include "userterminal.h"
#include "filedownthread.h"
#include "alarmsubstation.h"
#include "alarmquerythread.h"
#include "alarmstatusthread.h"
class AlarmWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AlarmWidget(QWidget *parent = 0);
    ~AlarmWidget();
    void setUserDevices(const QList<Userterminal> *devices)
    {
        userDevices=devices;
    }
    void setLabelSize(int w,int h);
    void initDevices();
    void setCurrentDevice(int i);
signals:
    void noAlarm();
private slots:
    void selectbt_click();
    void exportCsv();
    void managebt_click();
    void showImage(int,int);
    void setImage(QString);
    void deviceIdchange(int i);
    void queryDatas(QList<AlarmSubstation*> *);
    void updateStatus(int);
    void checkAll();
private:
    QLabel *deviceIdL;
    QComboBox *deviceId;
    QLabel *beginTimeL;
    QDateTimeEdit *beginTime;
    QLabel *endTimeL;
    QDateTimeEdit *endTime;

    QPushButton *selectbt;
    QPushButton *exportbt;

    QTableWidget* dataTable;
    QLabel* ima;

    QPushButton *managebt;
    QCheckBox *selectall;

    Filedownthread downt;
    const QList<Userterminal> *userDevices=NULL;
    const Userterminal *term;
    void initPanal();
    void initLayout();
    void initsolts();

    AlarmQueryThread queryt;
    const QList<AlarmSubstation*> *datas=nullptr;
    AlarmStatusThread updatet;

};

#endif // ALARMWIDGET_H
