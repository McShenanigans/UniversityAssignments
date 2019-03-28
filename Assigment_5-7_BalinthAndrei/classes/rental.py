from datetime import date, timedelta

class Rental():
    # initializes a rental with the necessary attributes
    def __init__(self, id, book, clientID, rentalDate=date.today(), returnDate="", dueDate=date.today()+timedelta(14)):
        self._id = id
        self._bookID = book.getID()
        self._clientID = clientID
        self._rentDate = rentalDate
        self._dueDate = dueDate
        self._returnDate = returnDate
        if str(returnDate) == "":
            book.setAvailability(False)
        book.incrementRentalsNumber()

    # returns the attributes of an instance formatted into a string
    def __str__(self):
        return "\n" + str(self._id) + ". Book " + str(self._bookID) + " to Client " + str(
            self._clientID) + "\n\tSince: " + str(self._rentDate) + "\n\tUntil: " + str(
            self._dueDate) + "\n\tReturned: " + str(self._returnDate)

    # return the ID of the rented book
    def getBookID(self):
        return self._bookID

    # return the ID of the client who rented the book
    def getClientID(self):
        return self._clientID

    # returns the date at which the book was returned
    def getReturnedDate(self):
        return str(self._returnDate)

    # sets the date at which a book was returned
    def setReturnedDate(self, date):
        self._returnDate = date

    # returns the ID of the rental
    def getID(self):
        return self._id

    # calculates the number of days a book was rented
    def durationInDays(self):
        if self._returnDate == "":
            return int(str((date.today() - self._rentDate).days))
        return int(str((self._returnDate - self._rentDate).days))

    # calculates the number of days whit which the due date of a book was exceeded
    def daysPastDueDate(self):
        if self._returnDate == "":
            return (int(str((date.today() - self._dueDate).days)) + abs(int(str((date.today() - self._dueDate).days))))/2
        return (int(str((self._returnDate - self._dueDate).days)) + abs(int(str((self._returnDate - self._dueDate).days))))/2
