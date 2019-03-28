class Book():
    # sets the attributes of a new book object
    def __init__(self, id, Title, Description, Author):
        self._id = id
        self._title = Title
        self._description = Description
        self._author = Author
        self._available = True
        self._rentalsNumber = 0

    # returns the numbers of times this book was rented
    def getRentalsNumber(self):
        return self._rentalsNumber

    # increments the number of times this book was rented
    def incrementRentalsNumber(self):
        self._rentalsNumber += 1

    # returns the ID of the book
    def getID(self):
        return self._id

    # returns the title of the book
    def getTitle(self):
        return self._title

    # returns the description of the book
    def getDescription(self):
        return self._description

    # returns the name of the book's author
    def getAuthor(self):
        return self._author

    # returns True if book is available for renting and False otherwise
    def getAvailability(self):
        return self._available

    # sets the book as available or unavailable
    def setAvailability(self, truthValue):
        self._available = truthValue

    # updates the book's title
    def updateTitle(self, newTitle):
        self._title = newTitle

    # updates the book's author
    def updateAuthor(self, newAuthor):
        self._author = newAuthor

    # updates the book's descripiton
    def updateDescription(self, newDescription):
        self._description = newDescription

    def __str__(self):
        return "\n" + str(self._id) + ". " + self._title + " by " + self._author + "\n\t" + self._description