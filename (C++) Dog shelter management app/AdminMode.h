#pragma once

#include <QWidget>
#include <QAction>
#include <QLabel>
#include <QDesktopServices>
#include <QUrl>
#include "controller.h"
#include <QLineEdit>
#include <QListWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include "ui_AdminMode.h"
#include "dogsTable.h"

class AdminMode : public QWidget
{
	Q_OBJECT

public:
	AdminMode(QWidget *parent = Q_NULLPTR);
	~AdminMode();
	void setController(controller * c);
	void setTable(dogsTable* tb);
	QLineEdit *getNameLE(), *getBreedLE(), *getAgeLE(), *getLinkLE();
	QPushButton *getClearBtn(), *getAddBtn(), *getRemoveBtn(), *getEditBtn(), *getExitBtn(), *getOpenBtn(), *getOpenLBtn(), *getUndoBtn(), *getRedoBtn();
	QListWidget *getListWidget();
	QLabel* getLabel();

private slots:
	void exit();
	void add();
	void remove();
	void edit();
	void openL();
	void openDoc();
	void onItemClicked();
	void undoFct();
	void redoFct();
	void clearBoard();

private:
	void updateList();
	Ui::AdminMode ui;
	int selectedDogId;
	controller* c;
	dogsTable* table;
	QListWidget listWid;
	QLabel lb;
	QLineEdit nameLE, breedLE, ageLE, linkLE;
	QAction *ctrlz, *ctrly;
	QPushButton clearBtn, addBtn, removeBtn, editBtn, exitBtn, openBtn, openLBtn, undoBtn, redoBtn;
};
