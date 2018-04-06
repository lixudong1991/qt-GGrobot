#ifndef INFOWIDGET_H
#define INFOWIDGET_H

#include<QWidget>
#include<QPaintEvent>
 class Infowidget : public QWidget
 {
        Q_OBJECT
public:
           explicit Infowidget(QWidget *parent = 0);
            ~Infowidget();
             void paintEvent(QPaintEvent*);
             void setTerminalId(const QString &s)
             {
                 terminalId=s;;
             }
             void setPos(const QString & i)
             {
                pos=i;
             }
             void setSonPos(const QString &i)
             {
                sonPos=i;
             }
             void setDatatype(const QString &i)
             {
                datatype=i;
             }
             void setData(const QString &i)
             {
                data=i;
             }
             void setSize(int width,int height)
             {
                 w=width;
                 h=height;
                 setFixedSize(w,h);
                 update();
             }
             void setReportTime(const QString &s)
             {
                 reportTime=s;;
             }
             void setElectricitys(const QString & i)
             {
                electricitys=i;
             }
             void setVoltage(const QString & i)
             {
                voltage=i;
             }
             void setElectricResidue(const QString & i)
             {
                electricResidue=i;
             }
             void setRobotStatus(const QString & i)
             {
                robotStatus=i;
             }
             void setRobotWorkMode(const QString & i)
             {
                robotWorkMode=i;
             }
             void setStatsTime(const QString & i)
             {
                statsTime=i;
             }
private:
            QString terminalId;
            QString reportTime;
            QString pos;
            QString sonPos;
            QString datatype;
            QString data;
            int w,h;
            QString statsTime;
            QString electricitys;
            QString voltage;
            QString electricResidue;
            QString robotStatus;
            QString robotWorkMode;
 };

#endif // INFOWIDGET_H
