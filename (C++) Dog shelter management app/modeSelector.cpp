#include "modeSelector.h"

modeSelector::modeSelector(QWidget *parent): QWidget(parent){
	label.setText("Please choose a mode");
	aBtn.setText("Administrator");
	gBtn.setText("Guest");
	eBtn.setText("Exit");
	connect(&aBtn, SIGNAL(released()), this, SLOT(adminBtn()));
	connect(&gBtn, SIGNAL(released()), this, SLOT(guestBtn()));
	connect(&eBtn, SIGNAL(released()), this, SLOT(exitBtn()));
	ui.setupUi(this);
}

void modeSelector::adminBtn() {
	*choice = 1;
	close();
}

void modeSelector::setChoice(int * c){
	choice = c;
}

QPushButton * modeSelector::getAdminBtn(){
	return &aBtn;
}

QPushButton * modeSelector::getGuestBtn(){
	return &gBtn;
}

QPushButton * modeSelector::getExitBtn(){
	return &eBtn;
}

QLabel * modeSelector::getLabel(){
	return &label;
}

void modeSelector::guestBtn(){
	*choice = 2;
	close();
}

void modeSelector::exitBtn(){
	*choice = 0;
	close();
}
