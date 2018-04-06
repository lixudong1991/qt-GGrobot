#ifndef MAINMENU_H
#define MAINMENU_H
#include "head.h"
class MainMenu : public QMenu
{
    Q_OBJECT

public:

    explicit MainMenu(QWidget *parent = 0);
    void translateActions();
signals:
    void showdbManage();
private slots:

private:

    void createActions();

private:
    QAction *dbManage;

};
#endif // MAINMENU_H
