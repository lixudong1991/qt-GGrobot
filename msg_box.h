#ifndef MSGBOX_H
#define MSGBOX_H


#include "head.h"
#include "push_button.h"
#include "dialog.h"

class MsgBox : public Dialog
{
	Q_OBJECT

public:

	explicit MsgBox(QWidget *parent = 0);
	~MsgBox();
	void translateLanguage();
	void setInfo(QString title_info, QString info, QPixmap pixmap, bool is_ok_hidden);

signals:

	void okMessageHidden(bool is_checked);
	void msgChecked(bool is_checked, bool is_ok);
	
private slots:

	void okOperate();
	void cancelOperate();

protected:

	void paintEvent(QPaintEvent *event);

private:

	QLabel *title_label;
	QLabel *title_icon_label;
	QLabel *msg_label; //提示图片
	QLabel *ask_label; //提示信息
	PushButton *close_button; //提示框上的关闭按钮
	QPushButton *ok_button; //下载按钮
	QPushButton *cancel_button; //取消按钮

	QString ok_text;
	QString cancel_text;

};

#endif  //MSGBOX_H
