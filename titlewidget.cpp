#include "titlewidget.h"
#include <mmsystem.h>
#pragma comment(lib,"WinMM.Lib")
TitleWidget::TitleWidget(QWidget *parent) :
    QWidget(parent)
{
    version_title = new QLabel();
    version_title->setStyleSheet("color:white");
    main_menu_button = new PushButton();
    close_button = new PushButton();
    min_button = new PushButton();

    main_menu_button->setPicName(QString(":/sysButton/menu"));
    close_button->setPicName(QString(":/sysButton/close"));
    min_button->setPicName(QString(":/sysButton/min"));

    connect(main_menu_button, SIGNAL(clicked()), this, SIGNAL(showMainMenu()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeWidget()));
    connect(min_button, SIGNAL(clicked()), this, SIGNAL(showMin()));

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(version_title,0,Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(0);

    QStringList string_list;
    string_list<<":/qss/content"<<":/qss/alarm"<<":/qss/export";
    QHBoxLayout *button_layout = new QHBoxLayout();

    QSignalMapper  *signal_mapper = new QSignalMapper(this);
     for(int i=0; i<string_list.size(); i++)
     {
        ToolButton *tool_button = new ToolButton(string_list.at(i));
        button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(turnPage(QString)));

    button_layout->setSpacing(8);
    button_layout->setContentsMargins(15, 0, 15, 0);
    button_layout->addStretch();

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(title_layout);
    main_layout->addLayout(button_layout);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    translateLanguage();

    setLayout(main_layout);
    setFixedHeight(100);
    is_move = false;

    flashTime=new QTimer;
    connect(flashTime,SIGNAL(timeout()),this,SLOT(flashTimeout()));
    muic=new QTimer;
    connect(muic,SIGNAL(timeout()),this,SLOT( muicTimeout()));
}
static BOOL MByteToWChar(LPCSTR lpcszStr, LPWSTR lpwszStr, DWORD)
{
    // Get the required size of the buffer that receives the Unicode
    // string.
    DWORD dwMinSize;
    dwMinSize = MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, NULL, 0);
    //assert(dwSize >= dwMinSize);

    // Convert headers from ASCII to Unicode.
    MultiByteToWideChar(CP_ACP, 0, lpcszStr, -1, lpwszStr, dwMinSize);
    return TRUE;
}

TitleWidget::~TitleWidget()
{

}
void TitleWidget::translateLanguage()
{
    main_menu_button->setToolTip(CH("配置信息"));
    close_button->setToolTip(CH("关闭"));
    min_button->setToolTip(CH("最小化"));

    button_list.at(0)->setText(CH("图像"));
    button_list.at(1)->setText(CH("历史告警"));
    button_list.at(2)->setText(CH("导出报表"));
}
void TitleWidget::turnPage(QString current_page)
{
    bool ok;
    int current_index = current_page.toInt(&ok, 10);

    for(int i=0; i<button_list.count(); i++)
    {
        ToolButton *tool_button = button_list.at(i);
        if(current_index == i)
        {
            tool_button->setMousePress(true);
        }
        else
        {
            tool_button->setMousePress(false);
        }
    }
    emit turnPage(current_index);
}
void TitleWidget::setAlarmBackground(bool b)
{
    if(b)
    {
        flashTime->start(500);
        muic->start(500);
        std::string s = "alarm.wav";
        wchar_t wText[30] = { 0 };
        MByteToWChar(s.c_str(), wText, sizeof(wText) / sizeof(wText[0]));
        PlaySound(wText, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
    }else
    {
        flashTime->stop();
        PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        button_list.at(1)->setIcon(QIcon(":/qss/alarm"));
    }
}
void TitleWidget::flashTimeout()
{
    static bool normal=true;
    if(normal)
    {
        button_list.at(1)->setIcon(QIcon(":/qss/repair"));
    }else{
        button_list.at(1)->setIcon(QIcon(":/qss/alarm"));
    }
    normal=!normal;   
}
void TitleWidget::muicTimeout()
{
    sec++;
    if(sec==10)
    {
         PlaySound(NULL, NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
         muic->stop();
         sec=0;
    }
}

void TitleWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setBrush(Qt::white);
    painter.drawPixmap(QRect(0, 0, this->width(), this->height()), QPixmap(":/qss/ba"));
}
