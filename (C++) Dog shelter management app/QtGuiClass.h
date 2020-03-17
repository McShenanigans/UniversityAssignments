#pragma once

#include <QWidget>
#include <QPushButton>
#include "ui_QtGuiClass.h"

class QtGuiClass : public QWidget
{
	Q_OBJECT

public:
	QtGuiClass(QWidget *parent = Q_NULLPTR);
	~QtGuiClass();
	void setChoice(int* c);
	QPushButton* getCVSBtn();
	QPushButton* getHTMLBtn();
private slots:
	void htmlBtn();
	void csvBtn();

private:
	int* choice;
	QPushButton csv, html;
	Ui::QtGuiClass ui;
};
