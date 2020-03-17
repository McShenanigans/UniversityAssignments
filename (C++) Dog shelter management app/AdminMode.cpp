#include "AdminMode.h"

AdminMode::AdminMode(QWidget *parent) : QWidget(parent) {
	ui.setupUi(this);
	addBtn.setText("Add dog");
	removeBtn.setText("Remove dog");
	editBtn.setText("Edit dog");
	exitBtn.setText("Log out");
	openBtn.setText("Open file");
	openLBtn.setText("Open Link");
	undoBtn.setText("Undo");
	redoBtn.setText("Redo");
	clearBtn.setText("Clear");
	ctrlz = new QAction("z", this);
	ctrly = new QAction("y", this);
	ctrlz->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
	ctrly->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));

	selectedDogId = -1;
	lb.setText("");
	lb.setStyleSheet("QLabel { color: red; }");
	connect(&exitBtn, SIGNAL(released()), this, SLOT(exit()));
	connect(&addBtn, SIGNAL(released()), this, SLOT(add()));
	connect(&removeBtn, SIGNAL(released()), this, SLOT(remove()));
	connect(&editBtn, SIGNAL(released()), this, SLOT(edit()));
	connect(&openLBtn, SIGNAL(released()), this, SLOT(openL()));
	connect(&openBtn, SIGNAL(released()), this, SLOT(openDoc()));
	connect(&redoBtn, SIGNAL(released()), this, SLOT(redoFct()));
	connect(ctrly, SIGNAL(triggered()), this, SLOT(redoFct()));
	connect(&undoBtn, SIGNAL(released()), this, SLOT(undoFct()));
	connect(ctrlz, SIGNAL(triggered()), this, SLOT(undoFct()));
	connect(&clearBtn, SIGNAL(released()), this, SLOT(clearBoard()));
	connect(&listWid, SIGNAL(itemSelectionChanged()), this, SLOT(onItemClicked()));
	this->addAction(ctrlz);
	this->addAction(ctrly);
}

AdminMode::~AdminMode() {
	delete ctrlz;
	delete ctrly;
}

void AdminMode::setController(controller * c){
	this->c = c;
	for (int i = 0; i < c->repoSize(); i++) {
		listWid.insertItem(0, new QListWidgetItem(c->getDogstring(i).c_str()));
	}
}

void AdminMode::setTable(dogsTable * tb){
	table = tb;
}

QLineEdit * AdminMode::getNameLE(){
	return &nameLE;
}

QLineEdit * AdminMode::getBreedLE(){
	return &breedLE;
}

QLineEdit * AdminMode::getLinkLE(){
	return &linkLE;
}

QLineEdit * AdminMode::getAgeLE(){
	return &ageLE;
}

QPushButton * AdminMode::getAddBtn(){
	return &addBtn;
}

QPushButton * AdminMode::getEditBtn(){
	return &editBtn;
}

QPushButton * AdminMode::getRemoveBtn(){
	return &removeBtn;
}

QPushButton * AdminMode::getOpenLBtn(){
	return &openLBtn;
}

QPushButton * AdminMode::getUndoBtn()
{
	return &undoBtn;
}

QPushButton * AdminMode::getRedoBtn()
{
	return &redoBtn;
}

QPushButton * AdminMode::getClearBtn()
{
	return &clearBtn;
}

QPushButton * AdminMode::getExitBtn(){
	return &exitBtn;
}

QPushButton * AdminMode::getOpenBtn(){
	return &openBtn;
}

QListWidget * AdminMode::getListWidget(){
	return &listWid;
}

QLabel * AdminMode::getLabel(){
	return &lb;
}

void AdminMode::add(){
	lb.setText("");
	QString name = nameLE.text();
	QString breed = breedLE.text();
	QString link = linkLE.text();
	QString age = ageLE.text();
	if (name == "" || breed == "" || age == "" || link == "") {
		lb.setText("Please fill in the entire form");
	}
	else {
		if (!(c->addDog(name.toStdString(), breed.toStdString(), age.toInt(), link.toStdString()))) {
			lb.setText("Operation unsuccesful. Please check the entered data.");
			c->saveChanges();
		}
		else {
			nameLE.setText("");
			breedLE.setText("");
			ageLE.setText("");
			linkLE.setText("");
			listWid.insertItem(0, new QListWidgetItem(c->getDogstring(c->repoSize() - 1).c_str()));
		}
	}
}

void AdminMode::remove(){
	lb.setText("");
	if (selectedDogId == -1) {
		lb.setText("Please select a dog.");
	}
	else {
		c->removeDog(selectedDogId);
		updateList();
	}
}

void AdminMode::edit(){
	lb.setText("");
	if (selectedDogId == -1) {
		lb.setText("Please select a dog.");
	}
	else {
		string name = nameLE.text().toStdString();
		string breed = breedLE.text().toStdString();
		string link = linkLE.text().toStdString();
		string age = ageLE.text().toStdString();
		if (name == "" || breed == "" || age == "" || link == "") {
			lb.setText("Please fill in the entire form");
		}
		else {
			c->editDog(selectedDogId, 1, name);
			c->editDog(selectedDogId, 2, breed);
			c->editDog(selectedDogId, 3, age);
			c->editDog(selectedDogId, 4, link);
			updateList();
		}
	}
}

void AdminMode::openL(){
	lb.setText("");
	if (selectedDogId == -1) {
		lb.setText("Please select a dog");
	}
	else {
		QString lnk = c->getLink(selectedDogId).c_str();
		QDesktopServices::openUrl(QUrl(lnk, QUrl::TolerantMode));
	}
}

void AdminMode::openDoc(){
	try { c->openFile(); }
	catch (exception& e) { lb.setText(e.what()); }
}

void AdminMode::onItemClicked(){
	if (listWid.currentItem() != nullptr) {
		QListWidgetItem* item = listWid.currentItem();
		QStringList items = item->text().split(".");
		selectedDogId = items[0].toInt();
		int index = c->getIndex(selectedDogId);
		nameLE.setText(c->getDogName(index).c_str());
		breedLE.setText(c->getDogBreed(index).c_str());
		ageLE.setText(to_string(c->getDogAge(index)).c_str());
		linkLE.setText(c->getDogLink(index).c_str());
	}
	else {
		nameLE.setText("");
		breedLE.setText("");
		ageLE.setText("");
		linkLE.setText("");
	}
}

void AdminMode::undoFct(){
	bool result = c->undo();
	if (result) updateList();
	else lb.setText("There are no actions to undo");
}

void AdminMode::redoFct(){
	bool result = c->redo();
	if(result)	updateList();
	else lb.setText("There are no actions to redo");
}

void AdminMode::clearBoard(){
	lb.setText("");
	nameLE.setText("");
	breedLE.setText("");
	ageLE.setText("");
	linkLE.setText("");
	selectedDogId = -1;
}

void AdminMode::updateList(){
	int i = 0;
	while(i + 1<listWid.count()) {
		QListWidgetItem* item = listWid.takeItem(0);
		delete item;
	}
	for (int j = 0; j < c->repoSize(); j++) {
		listWid.insertItem(1, new QListWidgetItem(c->getDogstring(j).c_str()));
	}
	QListWidgetItem* item = listWid.takeItem(0);
	delete item;
	table->update();
}

void AdminMode::exit(){
	table->close();
	close();
}
