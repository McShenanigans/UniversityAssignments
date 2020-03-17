#pragma once

#include <QtWidgets/QMainWindow>
#include <QPushButton>
#include <QLabel>
#include "ui_modeSelector.h"

class modeSelector : public QWidget
{
	Q_OBJECT

public:
	modeSelector(QWidget *parent = Q_NULLPTR);
	void setChoice(int* c);
	QPushButton* getAdminBtn();
	QPushButton* getGuestBtn();
	QPushButton* getExitBtn();
	QLabel* getLabel();
private slots:
	void adminBtn();
	void guestBtn();
	void exitBtn();
private:
	QPushButton aBtn, gBtn, eBtn;
	QLabel label;
	int* choice;
	Ui::modeSelectorClass ui;
};
