#pragma once
#include "controller.h"
#include <QAbstractTableModel>

class MyModel : public QAbstractTableModel
{
	Q_OBJECT
private:
	controller* c;

public:
	MyModel();
	~MyModel();
	void setController(controller* c);
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;
	QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	//bool setData(const QModelIndex &index, vector<string> args, int role = Qt::EditRole);
	
	//Qt::ItemFlags flags(const QModelIndex &index) const;
};
