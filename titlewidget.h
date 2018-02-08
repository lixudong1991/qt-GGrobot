#ifndef TITLEWIDGET_H
#define TITLEWIDGET_H
#include "head.h"
#include "tool_button.h"
#include "push_button.h"
class TitleWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TitleWidget(QWidget *parent = 0);
    void translateLanguage();
    ~TitleWidget();
    void setAlarmBackground(bool);
signals:

    void showMainMenu();
    void closeWidget();
    void showMin();
    void turnPage(int current_page);
protected:
    void paintEvent(QPaintEvent *);
public slots:
    void turnPage(QString current_page);

private slots:
    void flashTimeout();
private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;

    QLabel *version_title; //标题
    PushButton *main_menu_button; //主菜单
    PushButton *close_button; //关闭
    PushButton *min_button;
    QList<ToolButton *> button_list;

    QTimer *flashTime;
};

#endif // TITLEWIDGET_H
