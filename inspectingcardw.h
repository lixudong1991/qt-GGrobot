#ifndef INSPECTINGCARDW_H
#define INSPECTINGCARDW_H

#include "dialog.h"
#include "push_button.h"
#include "loading_widget.h"
#include <QTableWidget>
#include <QList>
#include <QPair>
class InspectingCardW :public Dialog
{
    Q_OBJECT

public:
    explicit InspectingCardW(QWidget *parent = 0);
    ~InspectingCardW();

    void setTableData(const QStringList &l);
    void setMsginfo(int);
private slots:
    void execbtClick();
    void checkAll();
signals:
    void checkCards(QList<int> *);
private:
    void initTitle();

    void getChecks();
private:
    QStackedLayout *login_stacked_layout;

    PushButton *close_button; //关闭按钮
    QLabel *title_label; //标题图标
    QWidget *title_wid;

    QTableWidget* cardTable;
    QWidget *tablewid;

    LoadingWidget *loading_widget;

    QWidget *msgW;
    QLabel *msg;

    QPushButton *execbt;
    QCheckBox *selectall;

    QList<int> checks;
    int rows;
};

#endif // INSPECTINGCARDW_H
