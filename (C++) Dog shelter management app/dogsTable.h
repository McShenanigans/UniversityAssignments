#pragma once
#include "MyModel.h"
#include <QTableView>
#include <QWidget>
#include "ui_dogsTable.h"

class dogsTable : public QWidget
{
	Q_OBJECT

public:
	dogsTable(QAbstractItemModel* m, QWidget *parent = Q_NULLPTR);
	~dogsTable();
	QTableView view;

private:
	QAbstractItemModel* model;
	Ui::dogsTable ui;
};
