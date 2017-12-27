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
    void showlogindia();
    void showdbset();
    void showdbManage();
private slots:

private:

    void createActions();

private:
    QAction *login; //
    QAction *dbset; //
    QAction *dbManage;

};
#endif // MAINMENU_H
