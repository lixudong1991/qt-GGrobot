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
    QPoint press_point;//��갴��ȥ�ĵ�
    bool is_move;

    QLabel *version_title; //����
    PushButton *main_menu_button; //���˵�
    PushButton *close_button; //�ر�
    PushButton *min_button;
    QList<ToolButton *> button_list;

    QTimer *flashTime;
};

#endif // TITLEWIDGET_H
