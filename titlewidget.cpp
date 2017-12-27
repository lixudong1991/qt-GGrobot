#include "titlewidget.h"
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
    string_list<<":/qss/content"<<":/qss/export";
    QHBoxLayout *button_layout = new QHBoxLayout();

    QSignalMapper *signal_mapper = new QSignalMapper(this);
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

   /* QPalette pal(palette());

    //设置背景黑色
    pal.setColor(QPalette::Background, Qt::black);
    setAutoFillBackground(true);
    setPalette(pal);*/

    setLayout(main_layout);
    setFixedHeight(100);
    is_move = false;
}

TitleWidget::~TitleWidget()
{

}
void TitleWidget::translateLanguage()
{
    version_title->setText(CH("�����豸����չʾ"));
    main_menu_button->setToolTip(CH("������Ϣ"));
    close_button->setToolTip(CH("�ر�"));
    min_button->setToolTip(CH("��С��"));

    button_list.at(0)->setText(CH("ͼ��"));
    button_list.at(1)->setText(CH("��������"));
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