#ifndef EXPORTWIDGET_H
#define EXPORTWIDGET_H

#include <QDateTimeEdit>
#include <QTableWidget>
#include "head.h"
#include "userterminal.h"
#include "substationdata.h"
#include "finddatathread.h"
#include "exportdownima.h"
#include "filedownthread.h"
#include "push_button.h"
class ExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExportWidget(QWidget *parent = 0);
    ~ExportWidget();
    void setLabelSize(int w,int h);
    void initData();
    void setUserDevices(const QList<Userterminal> *devices)
    {
        userDevices=devices;
    }
private slots:
    void deviceIdchange(int);
    void posSizeChange(QString);
    void exportCsv();
    void selectData();
    void getDatamap(QMap<int,QList<Substationdata*>*>*);
    void showImage(int,int);
    void setImage(QString);
    void  loadingtimeout();
private:
    QLabel *deviceIdL;
    QComboBox *deviceId;

    QLabel *beginTimeL;
    QDateTimeEdit *beginTime;

    QLabel *endTimeL;
    QDateTimeEdit *endTime;

    QLabel *beginPosL;
    QComboBox *beginPos;
    QLabel *endPosL;
    QComboBox *endPos;


    QPushButton *exportbt;
    QPushButton *selectbt;

    QTableWidget* dataTable;
    QComboBox *posbox;
    QLabel *ter_id;

    QLabel* ima;
    QLabel* info;

    const QList<Userterminal> *userDevices=NULL;
    const Userterminal *term;
    QMap<int,QList<Substationdata*>*> *data=NULL;
    FindDataThread thr;
    QMap<QString,QString> posNames;
    QMap<int,QString> posNumbers;

    void initLabel();
    void initPanal();
    void initsolts();

    ExportDownima *downima;
    Filedownthread downt;

    void selectDataThr(bool,const QString&);
   // void parseXML(const QString &fname);
};

#endif // EXPORTWIDGET_H
