from repositories.rentalRepository import RentalRepo
from datetime import date

class RentalController():
    def __init__(self):
        self._repo = RentalRepo()

    # creates a new entry in the rentals list
    def addRental(self, rental):
        self._repo.addRental(rental)

    # removes an entry from the rentals list
    def removeRental(self, id = -1, bookID = -1, clientID=-1, bookList = []):
        self._repo.removeRental(id, bookID, clientID, bookList)

    # returns the list of rentals
    def getAll(self):
        return self._repo.getAll()

    # returns a list of all the rentals with a given bookId or clientID
    def findRentals(self, bookID = -1, clientID = -1):
        results = []
        for rental in self._repo.getAll():
            if bookID != -1 and rental.getBookID == bookID:
                results.append(rental)
            elif clientID != -1 and rental.getClientID == clientID:
                results.append(rental)
        return results

    # sets the date on which a book was returned
    def setRentalReturnDate(self, id, date=date.today()):
        for rental in self._repo.getAll():
            if rental.getID() == id:
                rental.setReturnedDate(date)
                break

    # returns a list of the most rented authors, sorted in descending order
    def findMostRentedAuthors(self, bookManager):
        authors = {}
        for rent in self._repo.getAll():
            for book in bookManager:
                if book.getID() == rent.getBookID():
                    if book.getAuthor() not in authors.keys():
                        authors[book.getAuthor()] = 1
                    else:
                        authors[book.getAuthor()] += 1
        for book in bookManager:
            if book.getAuthor() not in authors.keys():
                authors[book.getAuthor()] = 0
        results = []
        for auth in authors:
            results.append(authorRentalCount(auth, authors[auth]))
        results.sort(reverse=True)
        return results

    # returns a list of the books in the book list, sorted in descending order of the number of days they were rented
    def findBooksRentedForMostDays(self, bookManager):
        books = {}
        for rent in self._repo.getAll():
            for book in bookManager:
                if book.getID() == rent.getBookID():
                    if book.getTitle() not in books.keys():
                        books[book.getTitle()] = rent.durationInDays()
                    else:
                        books[book.getTitle()] += rent.durationInDays()
                    break
        for book in bookManager:
            if book.getTitle() not in books.keys():
                books[book.getTitle()] = 0
        results = []
        for title in books:
            results.append(bookRentalDays(title, books[title]))
        results.sort(reverse=True)
        return results

    # returns a list of the clients from the clients list, sorted in descending order by the total number of days in which they had a book
    def findMostActiveClients(self, clientManager):
        clients = {}
        for rent in self._repo.getAll():
            for client in clientManager:
                if client.getID() == rent.getClientID():
                    if client not in clients.keys():
                        clients[client] = rent.durationInDays()
                    else:
                        clients[client] += rent.durationInDays()
        for client in clientManager:
            if client not in clients.keys():
                clients[client] = 0
        result = []
        for client in clients:
            result.append(clientRentalDays(client, clients[client]))
        result.sort(reverse=True)
        return result

    # returns a list of books that were not returned until their due date, sorted in descending order by the number of days by which the due date was exceeded
    def findLateRentals(self, bookManager):
        books = {}
        for rent in self._repo.getAll():
            if rent.daysPastDueDate() > 0:
                for book in bookManager:
                    if book.getID() == rent.getBookID():
                        if book.getTitle() not in books.keys():
                            books[book.getTitle()] = rent.daysPastDueDate()
                        else:
                            books[book.getTitle()] += rent.daysPastDueDate()
                        break
        results = []
        for book in books:
            results.append(bookRentalDays(book, books[book]))
        results.sort(reverse=True)
        return results

# an object which facilitates the comparison of 2 structures of the form [string, int] and provides a way to print it
class authorRentalCount:
    def __init__(self, book, count):
        self._book = book
        self._count = count

    def __str__(self):
        return str(self._count) + " - author: " + str(self._book)

    def __lt__(self, obj):
        return self._count < obj._count

    def __eq__(self, obj):
        return self._book == obj._book and self._count == obj._count

# an object which facilitates the comparison of 2 structures of the form [string, int] and provides a way to print it
class bookRentalDays:
    def __init__(self, book, days):
        self._book = book
        self._days = days

    def __str__(self):
        return str(self._days) + " days - book: " + str(self._book)

    def __lt__(self, obj):
        return self._days < obj._days

    def __eq__(self, obj):
        return self._days == obj._days and self._book == obj._book

# an object which facilitates the comparison of 2 structures of the form [client, int] and provides a way to print it
class clientRentalDays:
    def __init__(self, client, days):
        self._client = client
        self._days = days

    def __str__(self):
        return str(self._days) + " days - client: " + str(self._client) + "\n"

    def __lt__(self, obj):
        return self._days < obj._days

    def __eq__(self, obj):
        return self._days == obj._days and obj._client == self._client