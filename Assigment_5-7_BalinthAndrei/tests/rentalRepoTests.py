import unittest
from classes.rental import Rental
from classes.book import Book
from classes.client import Client
from repositories.rentalRepository import RentalRepo, authorRentalCount, bookRentalDays, clientRentalDays
from datetime import date, timedelta

class RentRepoTest(unittest.TestCase):
    # tests the addRental method
    def test_Add(self):
        repo = RentalRepo()
        repo.addRental(Rental(1, Book(1, "a", "b", "c"), 1))
        assert(len(repo.getAll()) == 1)

    # tests the removeRental method
    def test_Remove(self):
        repo = RentalRepo()
        repo.addRental(Rental(1, Book(1, "a", "b", "c"), 1))
        repo.removeRental(1)
        assert(len(repo.getAll()) == 0)

    # tests the setReturnedDate method
    def test_Return(self):
        repo = RentalRepo()
        repo.addRental(Rental(1, Book(1, "a", "b", "c"), 1))
        repo.setRentalReturnDate(1, date(2019, 7, 18))
        assert(repo.getAll()[0].getReturnedDate() == str(date(2019, 7, 18)))

    # sets up the lists necessary for the last 4 test from this document
    def setup(self, rentManager):
        book1 = Book(1, "Silmarillion", "Great book.", "J.R.R. Tolkien")
        book2 = Book(2, "Dune", "Great book.", "Frank Herbert")
        book3 = Book(3, "The Subtle Knife", "Great book.", "Philip Pullman")
        book4 = Book(4, "Minecraft: Ghidul Fermierului", "Get back to work.", "Mojang")
        book5 = Book(5, "Inainteaza in varsta cu gratie", "Singles only", "Kathleen Dowling Singh")
        books = [book1, book2, book3, book4, book5]
        client1 = Client(1, "Vasile Pushcashu")
        client2 = Client(2, "Gheorghe Bulan")
        client3 = Client(3, "Mircea Minune")
        client4 = Client(4, "Cristi din Banat")
        client5 = Client(5, "Morico Pintea")
        clients = [client1, client2, client3, client4, client5]
        for i in range(5):
            rentManager.addRental(
                Rental(i + 1, books[i], clients[i].getID(), date(2015, 5, 17),
                       date(2015, 5, 17) + timedelta(2 * i + 1), date(2015, 5, 17) + timedelta(6)))
        return books, clients

    # tests the findLateRentals method
    def test_LateRentals(self):
        rentManager = RentalRepo()
        lists = self.setup(rentManager)
        assert(len(rentManager.findLateRentals(lists[0])) == 2)

    # tests the findMostActiveClients method
    def test_ActiveClients(self):
        rentManager = RentalRepo()
        lists = self.setup(rentManager)
        results = rentManager.findMostActiveClients(lists[1])
        assert(results[0] == clientRentalDays(lists[1][4], 9))
        assert(results[1] == clientRentalDays(lists[1][3], 7))
        assert(results[2] == clientRentalDays(lists[1][2], 5))
        assert(results[3] == clientRentalDays(lists[1][1], 3))
        assert(results[4] == clientRentalDays(lists[1][0], 1))

    # tests the findBooksRentedForMostDays method
    def test_MostRented_Days(self):
        rentManager = RentalRepo()
        lists = self.setup(rentManager)
        results = rentManager.findBooksRentedForMostDays(lists[0])
        assert(results[0] == bookRentalDays(lists[0][4].getTitle(), 9))
        assert(results[1] == bookRentalDays(lists[0][3].getTitle(), 7))
        assert(results[2] == bookRentalDays(lists[0][2].getTitle(), 5))
        assert(results[3] == bookRentalDays(lists[0][1].getTitle(), 3))
        assert(results[4] == bookRentalDays(lists[0][0].getTitle(), 1))

    # tests the findMostRentedAuthors method
    def test_MostRentedAuthors(self):
        rentManager = RentalRepo()
        lists = self.setup(rentManager)
        rentManager.addRental(
            Rental(6, lists[0][2], 3, date.today(), date.today() + timedelta(7), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(7, lists[0][2], 3, date.today(), date.today() + timedelta(7), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(8, lists[0][2], 3, date.today(), date.today() + timedelta(7), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(9, lists[0][2], 3, date.today(), date.today() + timedelta(7), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(10, lists[0][1], 1, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(11, lists[0][1], 1, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(12, lists[0][1], 1, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(13, lists[0][3], 2, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(14, lists[0][3], 2, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        rentManager.addRental(
            Rental(15, lists[0][4], 2, date.today(), date.today() + timedelta(5), date.today() + timedelta(10)))
        results = rentManager.findMostRentedAuthors(lists[0])
        assert(results[0] == authorRentalCount(lists[0][2].getAuthor(), 5))
        assert(results[1] == authorRentalCount(lists[0][1].getAuthor(), 4))
        assert(results[2] == authorRentalCount(lists[0][3].getAuthor(), 3))
        assert(results[3] == authorRentalCount(lists[0][4].getAuthor(), 2))
        assert(results[4] == authorRentalCount(lists[0][0].getAuthor(), 1))

class RentTest(unittest.TestCase):
    # test the setReturnedDate method
    def test_SetReturnedDate(self):
        rental = Rental(1, Book(1, "a", "b", "c"), 1)
        rental.setReturnedDate(date(2019, 5, 17))
        assert(rental.getReturnedDate() == str(date(2019, 5, 17)))

    # tests the daysPastDueDate method
    def test_DaysPastDue(self):
        rent = Rental(1, Book(1, "a", "b", "c"), 1, date(2015, 6, 15), date(2015, 7, 15), date(2015, 6, 29))
        assert(rent.daysPastDueDate() == 16)
        rent1 = Rental(1, Book(1, "a", "b", "c"), 1, date(2015, 6, 15), date(2015, 6, 28), date(2015, 6, 29))
        assert(rent1.daysPastDueDate() == 0)

    # tezts the durationInDays method
    def test_DurationInDays(self):
        rent = Rental(1, Book(1, "a", "b", "c"), 1, date(2015, 6, 15), date(2015, 7, 15), date(2015, 6, 29))
        assert(rent.durationInDays() == 30)
        rent1 = Rental(1, Book(1, "a", "b", "c"), 1, date(2015, 6, 15), date(2015, 6, 29), date(2015, 6, 29))
        assert(rent1.durationInDays() == 14)

if __name__ == '__main__':
    unittest.main()