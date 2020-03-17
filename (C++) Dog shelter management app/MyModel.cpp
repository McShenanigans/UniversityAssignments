#include "MyModel.h"

MyModel::MyModel()
{
}

MyModel::~MyModel()
{
}

void MyModel::setController(controller * c){
	this->c = c;
}

int MyModel::rowCount(const QModelIndex & parent) const{
	return c->repoSize();
}

int MyModel::columnCount(const QModelIndex & parent) const{
	return 5;
}

QVariant MyModel::data(const QModelIndex & index, int role) const{
	int row = index.row();
	int col = index.column();
	if (role == Qt::DisplayRole) {
		if (col == 0) return QString::fromStdString(to_string(c->getDogID(row)));
		if (col == 1) return QString::fromStdString(c->getDogName(row));
		if (col == 2) return QString::fromStdString(c->getDogBreed(row));
		if (col == 3) return QString::fromStdString(to_string(c->getDogAge(row)));
		if (col == 4) return QString::fromStdString(c->getDogLink(row));
	}
	return QVariant();
}

QVariant MyModel::headerData(int section, Qt::Orientation orientation, int role) const{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
		if (section == 0) return "ID";
		if (section == 1) return "Name";
		if (section == 2) return "Breed";
		if (section == 3) return "Age";
		if (section == 4) return "Link";
	}
	return QVariant();
}
