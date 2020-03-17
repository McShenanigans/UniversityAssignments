#include "modeSelector.h"
#include "AdminMode.h"
#include "GuestMode.h"
#include "QtGuiClass.h"
#include "controller.h"
#include "MyModel.h"
#include "dogsTable.h"
#include <QtWidgets/QApplication>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QListWidget>

void initialize(controller &c) {
	if (c.repoSize() < 10) {
		c.addDog("Doge", "Shiba-Inu", 7, "https://www.youtube.com/watch?v=Yj7ja6BANLM", true);
		c.addDog("Spike", "GermanShepard", 10, "https://www.youtube.com/watch?v=bfHYS-P--F0", true);
		c.addDog("Dave", "Labrador", 5, "https://www.youtube.com/watch?v=in_jF1W3jUg", true);
		c.addDog("Mishka", "Husky", 7, "https://www.youtube.com/watch?v=qXo3NFqkaRM", true);
		c.addDog("Jack", "GoldenRetriever", 1, "https://www.youtube.com/watch?v=a6KGPBflhiM", true);
		c.addDog("Mimi", "YorkshireTerrier", 4, "https://www.youtube.com/watch?v=yujntyRK2qA", true);
		c.addDog("Tom", "Akita-Inu", 6, "https://www.youtube.com/watch?v=RZ3zg5KiXsg", true);
		c.addDog("Scooby-Doo", "GreatDane", 50, "https://www.youtube.com/watch?v=776rvGHfzuM", true);
		c.addDog("Jerry", "Chihuahua", 3, "https://www.youtube.com/watch?v=7PLuhK82Xjs", true);
		c.addDog("Toro", "Doberman", 8, "https://www.youtube.com/watch?v=GCM0phNqL0g", true);
	}
}

void adminMode(int argc, char* argv[], controller& c) {
	QApplication a(argc, argv);
	AdminMode admin{};
	MyModel model{};
	model.setController(&c);
	admin.setController(&c);
	dogsTable dt{ &model };
	QGridLayout gl{ &admin };
	admin.setTable(&dt);

	QListWidget *lw = admin.getListWidget();
	QLabel* errLb = admin.getLabel();
	QLineEdit *nameLE = admin.getNameLE(), *breedLE = admin.getBreedLE(), *ageLE = admin.getAgeLE(), *linkLE = admin.getLinkLE();
	QLabel nameL("Name"), breedL("Breed"), ageL("Age"), linkL("Link");
	QPushButton *addBtn = admin.getAddBtn(), *removeBtn = admin.getRemoveBtn(), *editBtn = admin.getEditBtn(), *exitBtn = admin.getExitBtn(), *openBtn = admin.getOpenBtn(), *openLBtn = admin.getOpenLBtn();
	QPushButton *undoBtn = admin.getUndoBtn(), *redoBtn = admin.getRedoBtn(), *clearBtn = admin.getClearBtn();
	gl.addWidget(errLb, 0, 0, 1, 3);
	gl.addWidget(&nameL, 1, 0);
	gl.addWidget(nameLE, 1, 1, 1, 2);
	gl.addWidget(&breedL, 2, 0);
	gl.addWidget(breedLE, 2, 1, 1, 2);
	gl.addWidget(&ageL, 3, 0);
	gl.addWidget(ageLE, 3, 1, 1, 2);
	gl.addWidget(&linkL, 4, 0);
	gl.addWidget(linkLE, 4, 1, 1, 2);
	gl.addWidget(addBtn, 5, 0);
	gl.addWidget(removeBtn, 5, 1);
	gl.addWidget(editBtn, 5, 2);
	gl.addWidget(openBtn, 7, 0);
	gl.addWidget(openLBtn, 7, 1);
	gl.addWidget(exitBtn, 7, 2);
	gl.addWidget(lw, 0, 3, 8, 7);
	gl.addWidget(undoBtn, 6, 0);
	gl.addWidget(redoBtn, 6, 1);
	gl.addWidget(clearBtn, 6, 2);

	QGridLayout glt{ &dt };
	glt.addWidget(&(dt.view));
	
	admin.show();
	dt.show();
	admin.setWindowTitle("Administrator mode");
	a.exec();
}

void guestMode(int argc, char* argv[], controller& c) {
	int adopt = 0;
	QApplication a(argc, argv);
	GuestMode guest{};
	guest.setController(&c);
	guest.setAdopt(&adopt);
	QGridLayout gl{ &guest };
	QPushButton *nextDog = guest.getNextBtn(), *addBtn = guest.getAddBtn(), *adoptBtn = guest.getAdoptBtn(), *cancelBtn = guest.getClearBtn(), *loBtn = guest.getExitBtn(), *searchBtn = guest.getSearchBtn(), *openBtn = guest.getOpenBtn();
	QLabel adoptL("Adoption list"), *name = guest.getNameL(), *breed = guest.getBreedL(), *age = guest.getAgeL(), *link = guest.getLinkL(), *result = guest.getResult();
	QLineEdit *searchLE = guest.getSearch();
	QListWidget *adoptionList = guest.getAdoptionList();

	gl.addWidget(new QLabel("Enter a breed"), 0, 0, 1, 4);
	gl.addWidget(searchLE, 1, 0, 1, 3);
	gl.addWidget(searchBtn, 1, 3);
	gl.addWidget(result, 2, 0, 1, 4);
	gl.addWidget(name, 3, 0, 1, 4);
	gl.addWidget(breed, 4, 0, 1, 4);
	gl.addWidget(age, 5, 0, 1, 4);
	gl.addWidget(link, 6, 0, 1, 4);
	gl.addWidget(openBtn, 7, 0, 1, 3);
	gl.addWidget(nextDog, 7, 3);
	gl.addWidget(addBtn, 8, 0, 1, 3);
	gl.addWidget(loBtn, 8, 3);
	gl.addWidget(&adoptL, 0, 4, 1, 2);
	gl.addWidget(adoptionList, 1, 4, 7, 3);
	gl.addWidget(adoptBtn, 8, 4);
	gl.addWidget(cancelBtn, 8, 5);

	guest.show();
	guest.setWindowTitle("Guest mode");
	a.exec();

	if (adopt) {
		vector<int> adoptions = guest.getAdoptions();
		for (int id : adoptions) c.removeDog(id);
	}
}

int selectMode(int argc, char* argv[]) {
	int choice;
	QApplication a(argc, argv);
	modeSelector w {};
	w.setChoice(&choice);
	QHBoxLayout hb{ &w };
	QLabel* lb = w.getLabel();
	QPushButton *adminBtn = w.getAdminBtn(), *guestBtn = w.getGuestBtn(), *exitBtn = w.getExitBtn();
	hb.addWidget(lb);
	hb.addWidget(adminBtn);
	hb.addWidget(guestBtn);
	hb.addWidget(exitBtn);
	w.show();
	w.setWindowTitle("Mode selector");
	a.exec();
	return choice;
}

int readFileType(int argc, char* argv[]) {
	int type = 0;
	QApplication a(argc, argv);
	QtGuiClass selector{};
	selector.setChoice(&type);
	QLabel lb("Please choose a file type to save to.");
	QPushButton* csv = selector.getCVSBtn(), *html = selector.getHTMLBtn();
	QHBoxLayout gl{ &selector };
	gl.addWidget(&lb);
	gl.addWidget(csv);
	gl.addWidget(html);
	selector.show();
	selector.setWindowTitle("FileType selector");
	a.exec();
	return type;
}

int main(int argc, char *argv[]){
	{
		int fileType = readFileType(argc, argv);
		int choice = selectMode(argc, argv);
		controller c{ fileType };
		c.initializeC();
		initialize(c);
		while (choice) {
			if (choice == 1) adminMode(argc, argv, c);
			else if (choice == 2) guestMode(argc, argv, c);
			else return 0;
			c.saveChanges();
			choice = selectMode(argc, argv);
		}
	}
	return 0;
}