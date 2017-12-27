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
private:
            QString terminalId;
            QString reportTime;
            QString pos;
            QString sonPos;
            QString datatype;
            QString data;
            int w,h;
 };

#endif // INFOWIDGET_H
