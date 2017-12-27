#ifndef EXPORTDOWNIMA_H
#define EXPORTDOWNIMA_H
#include "head.h"
#include "dialog.h"
#include "loading_widget.h"
class ExportDownima : public Dialog
{
    Q_OBJECT

public:

    explicit ExportDownima(QWidget *parent = 0);
    ~ExportDownima();
    void  loadingStart(bool,const QString&);

signals:
    void error();
protected:


private slots:
  void timeout();
private:
    LoadingWidget *loading_widget;
    QTimer *timer;
};
#endif
