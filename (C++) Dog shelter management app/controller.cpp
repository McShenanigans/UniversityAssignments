#include "controller.h"
#include <iostream>
#include <fstream>
#include <QDesktopServices>
#include <QUrl>

using namespace std;

controller::controller(int fileType) {
	if (fileType == 1) this->dogs = new CSVrepo<Dog>{};
	else this->dogs = new HTMLrepo<Dog>{};
	undoRepo = new UndoRepo<Dog>{};
	redoRepo = new UndoRepo<Dog>{};
}

bool controller::addDog(const string name, const string breed, const int age, const string photo, bool fromInit) {
	int id = 0;
	if (this->repoSize() > 0) {
		id = this->dogs->getItem(this->dogs->getRepoSize() - 1).getID() + 1;
	}
    Dog newDog{id, name, breed, age, photo};
	try {
		dogValidator dv;
		dv.validate(newDog);
		try {
			this->dogs->addEntry(newDog);
			if (!fromInit) {
				undoRepo->pushOperation("add", newDog);
				redoRepo->emptyRepo();
			}
			return true;
		}
		catch (exception& e) {
			return false;
		}
	}
	catch (exception& e) {
		return false;
	}
}

bool controller::removeDog(int id) {
	for (int i = 0; i < this->dogs->getRepoSize(); i++) {
		if (this->dogs->getItem(i).getID() == id) {
			try {
				Dog removedDog = dogs->getItem(i);
				this->dogs->removeEntry(i);
				undoRepo->pushOperation("remove", removedDog);
				redoRepo->emptyRepo();
				return true;
			}
			catch (exception& e) {}
		}
	}
	return false;
}

void controller::editDog(const int id, const int field, const string newValue) {
	for (int i = 0; i < this->dogs->getRepoSize(); i++) {
		Dog d = this->dogs->getItem(i);
		if (d.getID() == id) {
			Dog newDog{ d.getID(), d.getName(), d.getBreed(), d.getAge(), d.getPhoto()};
			Dog oldDog = dogs->getItem(i);
			if (field == 1) newDog.setName(newValue);
			else if (field == 2) newDog.setBreed(newValue);
			else if (field == 3) newDog.setAge(stoi(newValue));
			else if (field == 4) newDog.setPhoto(newValue);
			try {
				this->dogs->editEntry(i, newDog);
				undoRepo->pushOperation("edit", oldDog);
				redoRepo->emptyRepo();
			}
			catch(exception& e){}
		}
	}
}

void controller::saveChanges()
{
	vector<string> items;
	for (int i = 0; i < this->dogs->getRepoSize(); i++) {
		items.push_back(this->dogs->getItem(i).dogStringSimple());
	}
	this->dogs->writeToFile(items);
	ofstream f("dogs.txt", ios::trunc);
	this->dogs->reset();
	while (this->dogs->isValid()) {
		f << this->dogs->getCurrentItem();
		this->dogs->next();
	}
	f.close();
}

void controller::openFile()
{
	if (this->dogs->getRepoSize() == 0) throw myException("There are no dogs to display");
	QDesktopServices::openUrl(QUrl::fromLocalFile(dogs->getOutputFile().c_str()));
}


void controller::initializeC()
{
	ifstream f("dogs.txt");
	if (!f.is_open()) return;
	string file;
	while (!f.eof()) {
		Dog d{};
		f >> d;
		try {
			dogValidator dv;
			dv.validate(d);
			try {
				this->dogs->addEntry(d);
			}
			catch (exception& e) {}
		}
		catch (exception& e) {}
	}
	f.close();
}

bool controller::undo(){
	try {
		string lastOp = undoRepo->lastOperation();
		Dog lastDog = undoRepo->lastObj();
		redoRepo->pushOperation(lastOp, lastDog);
		if (lastOp == "add") {
			for (int i = 0; i < dogs->getRepoSize(); i++) {
				if (dogs->getItem(i).getID() == lastDog.getID()) {
					dogs->removeEntry(i);
				}
			}
		}
		else if (lastOp == "remove") {
			dogs->addEntry(lastDog);
		}
		else if (lastOp == "edit") {
			for (int i = 0; i < dogs->getRepoSize(); i++) {
				if (dogs->getItem(i).getID() == lastDog.getID())
					dogs->editEntry(i, lastDog);
			}
		}
		return true;
	}
	catch(exception& e) {
		return false;
	}
}

bool controller::redo(){
	try {
		string lastOp = redoRepo->lastOperation();
		Dog lastDog = redoRepo->lastObj();
		undoRepo->pushOperation(lastOp, lastDog);
		if (lastOp == "add") {
			dogs->addEntry(lastDog);
		}
		else if (lastOp == "remove") {
			for (int i = 0; i < dogs->getRepoSize(); i++) {
				if (dogs->getItem(i).getID() == lastDog.getID())
					dogs->removeEntry(i);
			}
		}
		else if (lastOp == "edit") {
			for (int i = 0; i < dogs->getRepoSize(); i++) {
				if (dogs->getItem(i).getID() == lastDog.getID())
					dogs->editEntry(i, lastDog);
			}
		}
		return true;
	}
	catch (exception& e) {
		return false;
	}
}

int controller::repoSize() {
    return this->dogs->getRepoSize();
}

int controller::getDogs(const string breed, int *found) {
    int i = 0;
    if (breed.empty()) {
        this->dogs->reset();
        while (this->dogs->isValid()) {
            found[i] = this->dogs->getCurrentItem().getID();
            i++;
            this->dogs->next();
        }
        this->dogs->reset();
    } else {
        this->dogs->reset();
        while (this->dogs->isValid()) {
            if (this->dogs->getCurrentItem().getBreed() == breed) {
                found[i] = this->dogs->getCurrentItem().getID();
                i++;
            }
            this->dogs->next();
        }
        this->dogs->reset();
    }
    return i;
}

const string controller::getDogstring(int index) {
    return this->dogs->getItem(index).dogString();
}

const string controller::getDogstringID(int id) {
    for (int i = 0; i < this->repoSize(); i++) {
        if (this->dogs->getItem(i).getID() == id)
            return this->getDogstring(i);
    }
    return "";
}

const string controller::getDogName(int index) const{
	Dog d = this->dogs->getItem(index);
	return d.getName();
}

const string controller::getDogBreed(int index) const
{
	Dog d = this->dogs->getItem(index);
	return d.getBreed();
}

const string controller::getDogLink(int index) const
{
	Dog d = this->dogs->getItem(index);
	return d.getPhoto();
}

const int controller::getDogAge(int index) const
{
	Dog d = this->dogs->getItem(index);
	return d.getAge();
}

const int controller::getDogID(int index) const
{
	Dog d = this->dogs->getItem(index);
	return d.getID();
}

const string controller::getLink(int id){
    for (int i = 0; i < this->repoSize(); i++) {
        if (this->dogs->getItem(i).getID() == id)
            return this->dogs->getItem(i).getPhoto();
    }
    return "https://www.youtube.com/watch?v=X7rAnaKId3E";
}

const int controller::getIndex(int id)
{
	for (int i = 0; i < this->repoSize(); i++) {
		if (this->dogs->getItem(i).getID() == id)
			return i;
	}
	return -1;
}

controller::~controller(){
	delete this->dogs;
	delete undoRepo;
	delete redoRepo;
}
