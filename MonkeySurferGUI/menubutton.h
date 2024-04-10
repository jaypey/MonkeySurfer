#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <QPushButton>

class MenuButton : public QPushButton
{
public:
	MenuButton(const QString& text, QWidget* parent = nullptr) : QPushButton(text, parent) {
		QString str2 = "QPushButton:hover{color: #32a150; background: none; border: none;}"
			"QPushButton {"
			"font-size: 30px;"
			"background: none; border: none;"
			"color: #32a852;"
			" height: 30px;}"
			"QPushButton:pressed {background: none; border: none;"
			"color: #1f472a;}";
		setMaximumWidth(300);
		setMinimumHeight(100);
		setStyleSheet(str2);
	}
private:

};

#endif // !MENUBUTTON_H

