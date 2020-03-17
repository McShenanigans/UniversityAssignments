#include "dogsTable.h"

dogsTable::dogsTable(QAbstractItemModel* m, QWidget *parent)
	: QWidget(parent)
{
	this->model = m;
	view.setModel(m);
	ui.setupUi(this);
}

dogsTable::~dogsTable()
{
}
