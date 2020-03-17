#include "GuestMode.h"

GuestMode::GuestMode(QWidget *parent) : QWidget(parent){
	nextBtn.setText("next");
	addBtn.setText("Add to adoption list");
	adoptBtn.setText("Adopt dogs");
	clearBtn.setText("Clear list");
	openLBtn.setText("open link in browser");
	searchBtn.setText("search");
	exitBtn.setText("Log out");
	name.setText("");
	breed.setText("");
	age.setText("");
	link.setText("");
	result.setStyleSheet("QLabel {color: red;}");
	adoptionList.setMinimumWidth(200);
	search.setMinimumWidth(150);

	connect(&exitBtn, SIGNAL(released()), this, SLOT(exit()));
	connect(&nextBtn, SIGNAL(released()), this, SLOT(next()));
	connect(&addBtn, SIGNAL(released()), this, SLOT(add()));
	connect(&clearBtn, SIGNAL(released()), this, SLOT(clear()));
	connect(&searchBtn, SIGNAL(released()), this, SLOT(searchFunction()));
	connect(&search, SIGNAL(editingFinished()), this, SLOT(searchFunction()));
	connect(&openLBtn, SIGNAL(released()), this, SLOT(openLnk()));
	connect(&adoptBtn, SIGNAL(released()), this, SLOT(adopt()));

	currentDog = 0;
	ui.setupUi(this);
}

GuestMode::~GuestMode() {}

QPushButton * GuestMode::getNextBtn()
{
	return &nextBtn;
}

QPushButton * GuestMode::getAddBtn()
{
	return &addBtn;
}

QPushButton * GuestMode::getAdoptBtn()
{
	return &adoptBtn;
}

QPushButton * GuestMode::getExitBtn()
{
	return &exitBtn;
}

QPushButton * GuestMode::getOpenBtn()
{
	return &openLBtn;
}

QPushButton * GuestMode::getClearBtn()
{
	return &clearBtn;
}

QPushButton * GuestMode::getSearchBtn()
{
	return &searchBtn;
}

QLabel * GuestMode::getNameL()
{
	return &name;
}

QLabel * GuestMode::getLinkL()
{
	return &link;
}

QLabel * GuestMode::getBreedL()
{
	return &breed;
}

QLabel * GuestMode::getAgeL()
{
	return &age;
}

QLabel * GuestMode::getResult()
{
	return &result;
}

QLineEdit * GuestMode::getSearch(){
	return &search;
}

QListWidget * GuestMode::getAdoptionList(){
	return &adoptionList;
}

void GuestMode::setController(controller * c){
	this->c = c;
	if (c->repoSize() > 0) {
		for (int i = 0; i < c->repoSize(); i++) {
			list.push_back(i);
		}
		name.setText(c->getDogName(0).c_str());
		breed.setText(c->getDogBreed(0).c_str());
		link.setText(c->getDogLink(0).c_str());
		age.setText(to_string(c->getDogAge(0)).c_str());
		currentDog = 0;
	}
	else {
		result.setText("There are no dogs to adopt");
	}
}

void GuestMode::setAdopt(int * choice){
	this->willAdopt = choice;
}

vector<int> GuestMode::getAdoptions()
{
	return adoptions;
}

void GuestMode::next(){
	result.setText("");
	if (adoptions.size() != list.size()) {
		currentDog++;
		if (currentDog == list.size()) currentDog = 0;
		bool ok = true;
		for (int i = 0; i < adoptions.size(); i++) {
			if (c->getDogID(list[currentDog]) == adoptions[i]) {
				ok = false;
				break;
			}
		}
		if (ok) {
			name.setText(c->getDogName(list[currentDog]).c_str());
			breed.setText(c->getDogBreed(list[currentDog]).c_str());
			link.setText(c->getDogLink(list[currentDog]).c_str());
			age.setText(to_string(c->getDogAge(list[currentDog])).c_str());
		}
		else next();
	}
	else { 
		result.setText("There are no more dogs to show.");
		name.setText("");
		age.setText("");
		link.setText("");
		breed.setText("");
		currentDog = -1;
	}
}

void GuestMode::add(){
	if (currentDog != -1) {
		adoptions.push_back(c->getDogID(list[currentDog]));
		adoptionList.insertItem(0, new QListWidgetItem(c->getDogstring(list[currentDog]).c_str()));
		next();
	}
	else {
		result.setText("Cannot add this dog");
	}
}

void GuestMode::clear(){
	adoptionList.clear();
	adoptions.clear();
	result.setText("");
	if(currentDog == -1) next();
}

void GuestMode::searchFunction(){
	if (search.text() == "") {
		list.clear();
		for (int i = 0; i < c->repoSize(); i++)
			list.push_back(i);
	}
	else {
		list.clear();
		QString breed = search.text();
		for (int i = 0; i < c->repoSize(); i++) {
			QString cBreed = c->getDogBreed(i).c_str();
			if (breed == cBreed) list.push_back(i);
		}
	}
	currentDog = -1;
	next();
}

void GuestMode::adopt(){
	*willAdopt = 1;
	close();
}

void GuestMode::openLnk(){
	if (c->repoSize() > 0) {
		QString lnk = c->getDogLink(list[currentDog]).c_str();
		QDesktopServices::openUrl(QUrl(lnk, QUrl::TolerantMode));
	}
}

void GuestMode::exit(){
	result.setText("");
	if (*willAdopt == 0 && adoptionList.count() != 0) {
		result.setText("Please confirm adoptions or clear list.");
	}
	else {
		close();
	}
}
