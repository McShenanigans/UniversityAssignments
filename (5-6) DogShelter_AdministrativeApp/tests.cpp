#include "Dog.h"
#include "controller.h"
#include "DynamicArray.h"
#include "generalTools.h"
#include "repository.h"
#include <assert.h>

void testDog() {
	{
		Dog dog;
		string name = "th", photo = "asd", breed = "asd";
		int id = 0, age = 12;
		Dog newDog{ 0, "th", "asd", 12, "asd" };
		assert(newDog.getAge() == age);
		assert(newDog.getBreed() == breed);
		assert(newDog.getPhoto() == photo);
		assert(newDog.getName() == name);
		assert(newDog.getID() == id);

		newDog.setAge(13);
		assert(newDog.getAge() == 13);

		breed = "dsa";
		newDog.setBreed(breed);
		assert(newDog.getBreed() == breed);

		name = "th1";
		newDog.setName(name);
		assert(newDog.getName() == name);

		photo = "das";
		newDog.setPhoto(photo);
		assert(newDog.getPhoto() == photo);

		string strForm = "0. th1: breed - dsa; age - 13; photoLink - das";
		assert(newDog.dogString() == strForm);

		Dog d{ 0, name, breed, newDog.getAge(), photo };
		assert((d == newDog) == true);
	}
}

void testTools() {
	int* arr = new int[3];
	arr[0] = 42;
	arr[1] = 15;
	arr[2] = 69;
	string str = "12";
	assert(inList(42, arr, 3) == true);
	assert(inList(40, arr, 3) == false);
	assert(intToString(12) == str);
	delete[] arr;
}

void testDynamicArray() {
	{
		DynamicArray<Dog> arr;
		assert(arr.getSize() == 0);
		Dog dog1{ 0, "th", "asd", 12, "asad" }, dog2{ 1, "th1", "def", 10, "dec" }, dog3{ 2, "th2", "fer", 15, "fgr" };

		arr.add(dog1);
		assert(arr.getSize() == 1);
		assert(arr.add(dog2) == true);
		assert(arr.add(dog2) == false);
		arr.add(dog3);
		assert(arr.getSize() == 3);

		assert(arr.remove(dog2.getID()) == true);
		assert(arr.remove(dog2.getID()) == false);
		assert(arr.getSize() == 2);

		assert(arr[0] == dog1);

		string name = "th5", breed = "labrat", link = "asdaw", age = "13";

		assert(arr.editEntry(dog1.getID(), 1, name) == true);
		assert(arr[0].getName() == name);

		assert(arr.editEntry(dog1.getID(), 2, breed) == true);
		assert(arr[0].getBreed() == breed);

		assert(arr.editEntry(dog1.getID(), 4, link) == true);
		assert(arr[0].getPhoto() == link);

		assert(arr.editEntry(dog1.getID(), 3, age) == true);
		assert(arr[0].getAge() == stoi(age));

		assert(arr.editEntry(6, 3, age) == false);
	}
}

void testRepo() {
	{
		repository<Dog> repo;
		Dog dog1{ 0, "th", "asd", 12, "asad" }, dog2{ 1, "th1", "def", 10, "dec" }, dog3{ 2, "th2", "fer", 15, "fgr" };

		assert(repo.addEntry(dog1) == true);
		assert(repo.addEntry(dog1) == false);
		repo.addEntry(dog2);
		repo.addEntry(dog3);
		assert(repo.getRepoSize() == 3);

		assert(repo.removeEntry(dog2.getID()) == true);
		assert(repo.removeEntry(dog2.getID()) == false);
		assert(repo.getRepoSize() == 2);

		assert(repo.isValid() == true);

		repo.next();
		repo.next();
		assert(repo.isValid() == false);

		repo.reset();
		assert(repo.isValid() == true);

		assert(repo.getItem(0) == dog1);
		assert(repo.getCurrentItem() == dog1);

		string name = "th5", breed = "labrat", link = "asdaw", age = "13";

		repo.editEntry(dog1.getID(), 1, name);
		assert(repo.getItem(0).getName() == name);

		repo.editEntry(dog1.getID(), 2, breed);
		assert(repo.getItem(0).getBreed() == breed);

		repo.editEntry(dog1.getID(), 4, link);
		assert(repo.getItem(0).getPhoto() == link);

		repo.editEntry(dog1.getID(), 3, age);
		assert(repo.getItem(0).getAge() == stoi(age)); 
	}
}

void testController() {
	{
		controller c;
		string name1 = "n1", name2 = "n2", name3 = "n3";
		string breed1 = "b1", breed2 = "b2", breed3 = "b3";
		string photo1 = "p1", photo2 = "p2", photo3 = "p3";
		int age1 = 12, age2 = 5, age3 = 9;

		assert(c.repoSize() == 0);
		assert(c.addDog(name1, breed1, age1, photo1) == true);
		assert(c.addDog(name1, breed1, age1, photo1) == false);
		c.addDog(name2, breed2, age2, photo2);
		c.addDog(name3, breed3, age3, photo3);
		assert(c.repoSize() == 3);

		assert(c.removeDog(1) == true);
		assert(c.removeDog(1) == false);
		assert(c.repoSize() == 2);

		string strDog = "0. " + name1 + ": breed - " + breed1 + "; age - " + intToString(age1) + "; photoLink - " + photo1;
		assert(c.getDogstring(0) == strDog);
		assert(c.getDogstringID(0) == strDog);
		assert(c.getDogstringID(6) == "");
		assert(c.getLink(6) == "https://www.youtube.com/watch?v=X7rAnaKId3E");

		assert(c.getLink(0) == photo1);

		int *found = new int[c.repoSize()];
		int len = c.getDogs("", found);
		delete[] found;
		assert(len == 2);

		found = new int[c.repoSize()];
		len = c.getDogs(breed1, found);
		delete[] found;
		assert(len == 1);

		string name4 = "n4", breed4 = "b4", photo4 = "p4", age4 = "80";
		c.editDog(0, 1, name4);
		c.editDog(0, 2, breed4);
		c.editDog(0, 3, age4);
		c.editDog(0, 4, photo4);

		strDog = "0. " + name4 + ": breed - " + breed4 + "; age - " + age4 + "; photoLink - " + photo4;
		assert(c.getDogstringID(0) == strDog);
	}
}

void testAll() {
	testDog();
	testTools();
	testDynamicArray();
	testRepo();
	testController();
}