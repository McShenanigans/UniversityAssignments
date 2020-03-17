#include "QtGuiClass.h"

QtGuiClass::QtGuiClass(QWidget *parent) : QWidget(parent){
	csv.setText("CSV");
	html.setText("HTML");
	connect(&csv, SIGNAL(released()), this, SLOT(csvBtn()));
	connect(&html, SIGNAL(released()), this, SLOT(htmlBtn()));
	ui.setupUi(this);
}

QtGuiClass::~QtGuiClass(){}

void QtGuiClass::setChoice(int * c){
	choice = c;
}

QPushButton * QtGuiClass::getCVSBtn(){
	return &html;
}

QPushButton * QtGuiClass::getHTMLBtn(){
	return &csv;
}

void QtGuiClass::htmlBtn(){
	*choice = 2;
	close();
}

void QtGuiClass::csvBtn(){
	*choice = 1;
	close();
}
