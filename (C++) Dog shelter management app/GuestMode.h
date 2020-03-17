#pragma once

#include <QWidget>
#include <QPushButton>
#include <QDesktopServices>
#include <QUrl>
#include <QLineEdit>
#include <QlistWidget>
#include <QLabel>
#include "controller.h"
#include "ui_GuestMode.h"

class GuestMode : public QWidget
{
	Q_OBJECT

public:
	GuestMode(QWidget *parent = Q_NULLPTR);
	~GuestMode();
	QPushButton *getNextBtn(), *getAddBtn(), *getAdoptBtn(), *getClearBtn(), *getExitBtn(), *getOpenBtn(), *getSearchBtn();
	QLabel *getNameL(), *getBreedL(), *getAgeL(), *getLinkL(), *getResult();
	QLineEdit *getSearch();
	QListWidget *getAdoptionList();
	void setController(controller* c);
	void setAdopt(int* choice);
	vector<int> getAdoptions();

private slots:
	void exit();
	void next();
	void add();
	void clear();
	void searchFunction();
	void adopt();
	void openLnk();

private:
	Ui::GuestMode ui;
	controller* c;
	int* willAdopt;
	int currentDog;
	vector<int> adoptions, list;
	QPushButton nextBtn, addBtn, adoptBtn, clearBtn, exitBtn, openLBtn, searchBtn;
	QLabel name, breed, age, link, result;
	QLineEdit search;
	QListWidget adoptionList;
};
