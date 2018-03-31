#include "inspectingcardw.h"
#include <QHeaderView>
InspectingCardW::InspectingCardW(QWidget *parent) :
    Dialog(parent)
{
    resize(300, 500);

    initTitle();

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(title_wid);
    title_layout->setSpacing(0);
    title_layout->setContentsMargins(5, 5, 5, 5);

    cardTable=new QTableWidget();
    QStringList  HStrList;
    HStrList.push_back(CH("λ������"));
    HStrList.push_back(CH("ѡ��"));
    cardTable->horizontalHeader()->setStretchLastSection(true);
    cardTable->horizontalHeader()->setEnabled(false);
    cardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    cardTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    cardTable->setColumnCount(HStrList.count());
    cardTable->setHorizontalHeaderLabels(HStrList);
    cardTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    cardTable->verticalHeader()->setVisible(true);
    cardTable->horizontalHeader()->resizeSection(0,180);
    cardTable->horizontalHeader()->resizeSection(1,50);

     tablewid=new QWidget(this);
     loading_widget = new LoadingWidget(this);
     msgW=new QWidget(this);
     msg=new QLabel();

     QHBoxLayout *lmsg=new QHBoxLayout(msgW);
     lmsg->addWidget(msg);
     lmsg->setContentsMargins(130,20,20,20);

     login_stacked_layout = new QStackedLayout();
     login_stacked_layout->addWidget(tablewid);
     login_stacked_layout->addWidget(loading_widget);
     login_stacked_layout->addWidget(msgW);
     login_stacked_layout->setCurrentWidget(tablewid);

    QVBoxLayout *cardLay=new QVBoxLayout();
    cardLay->addWidget(cardTable);
    cardLay->setContentsMargins(15, 10, 15 ,5);
    tablewid->setLayout(cardLay);

    execbt=new QPushButton(CH("��ʼִ��"));
    execbt->setFixedSize(60,20);
    selectall=new QCheckBox();
    QHBoxLayout *hb=new QHBoxLayout();
    hb->addStretch(2);
    hb->addWidget(execbt);
    hb->addStretch(1);
    hb->addWidget(new QLabel(CH("ȫѡ")));
    hb->addWidget(selectall);
    hb->setContentsMargins(15,0,15,20);

    QVBoxLayout *main_layout = new QVBoxLayout(this);
    main_layout->addLayout(title_layout);
    main_layout->addLayout(login_stacked_layout);
    main_layout->addLayout(hb);
    main_layout->setContentsMargins(SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH, SHADOW_WIDTH);

    connect(execbt, SIGNAL(clicked()), this, SLOT(execbtClick()));
    connect(selectall, SIGNAL(clicked()), this, SLOT(checkAll()));
}

InspectingCardW::~InspectingCardW()
{
}
void InspectingCardW::initTitle()
{
    title_label = new QLabel(CH("ѡ��λ��"));
    close_button = new PushButton();
    close_button->setPicName(QString(":/sysButton/close"));
    title_wid= new QWidget(this);

    QHBoxLayout * title_layout = new QHBoxLayout();
    title_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    title_layout->addStretch();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->setSpacing(5);
    title_layout->setContentsMargins(5, 5, 5, 5);

    QPalette pal;
    pal.setColor(QPalette::Background, Qt::black);
    title_wid->setAutoFillBackground(true);
    title_wid->setPalette(pal);
    title_wid->setFixedHeight(30);
    title_wid->setLayout(title_layout);

    connect(close_button, SIGNAL(clicked()), this, SLOT(close()));
}

void  InspectingCardW::execbtClick()
{
        QWidget *current_widget = login_stacked_layout->currentWidget();
        if(current_widget == tablewid)
        {
                execbt->setText(CH("����"));
                loading_widget->setAccount(CH("����ִ������"));
                login_stacked_layout->setCurrentWidget(loading_widget);
                loading_widget->start(true);
                getChecks();
        }else{
                execbt->setText(CH("��ʼִ��"));
                login_stacked_layout->setCurrentWidget(tablewid);
                loading_widget->start(false);
        }
}

void InspectingCardW::setTableData(const QStringList &l)
 {
        checks.clear();
        cardTable->clearContents();
        cardTable->setRowCount(l.size());
        rows=l.size();
        for(int j=0;j<l.size();j++)
        {
            QTableWidgetItem *item0=new QTableWidgetItem(l.at(j));
            item0->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            cardTable->setItem(j,0,item0);

            QTableWidgetItem *item1=new QTableWidgetItem();
            item1->setCheckState(Qt::Unchecked);
            item1->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
            cardTable->setItem(j,1,item1);
        }

 }
void InspectingCardW::getChecks()
{
    checks.clear();
    for(int i=0;i<rows;i++)
    {
        if(cardTable->item(i,1)->checkState()==Qt::Checked)
        {
            checks.append(i);
        }
    }
    emit checkCards(&checks);
}
void InspectingCardW::checkAll()
{
    auto sta=selectall->checkState();
    for(int i=0;i<rows;i++)
    {
        cardTable->item(i,1)->setCheckState(sta);
    }
}
void InspectingCardW::setMsginfo(int status)
{
        loading_widget->start(false);
        execbt->setText(CH("����"));
        QString msgstr;
        switch (status) {
        case 0:
               msgstr=CH("����ִ�гɹ�");
            break;
        case 1:
             msgstr=CH("�����������Զ�Ѳ��");
            break;
        case 2:
             msgstr=CH("���������ڳ��");
            break;
        case 3:
             msgstr=CH("�����������ض�Ѳ��");
            break;
        case 4:
             msgstr=CH("��������ʧ��");
            break;
        default:
             msgstr=CH("δ֪����");
            break;
        }
        msg->setText(msgstr);
        login_stacked_layout->setCurrentWidget(msgW);
}
