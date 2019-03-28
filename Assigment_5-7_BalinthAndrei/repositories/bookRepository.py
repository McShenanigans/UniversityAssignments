from classes.ui import UI

class BookRepo:
    # creates an empty list in which the books are kept
    def __init__(self):
        self._list = []

    # creates a new entry in the list of books
    def addBook(self, book):
        self._list.append(book)

    # removes an entry from the list of books
    def removeBook(self, id):
        self._list1 = []
        for book in self._list:
            if book.getID() != id:
                self._list1.append(book)
        self._list = self._list1

    # return the list of books
    def getAll(self):
        return self._list

    # updates the attributes of the book the user chose to update
    # def updateBook(self, id, attributes, title="", desc="", author=""):
    #     for book in self._list:
    #         if book.getID() == id:
    #             for att in attributes:
    #                 if att == "title":
    #                     if title == "":
    #                         book.updateTitle(UI().updateBookTitle())
    #                     else:
    #                         book.updateTitle(title)
    #                 if att == "author":
    #                     if author == "":
    #                         book.updateAuthor(UI().updateBookAuthor())
    #                     else:
    #                         book.updateAuthor(author)
    #                 if att == "description":
    #                     if desc == "":
    #                         book.updateDescription(UI().updateBookDescription())
    #                     else:
    #                         book.updateDescription(desc)
    #             break

    # updates the availability of the book
    # def updateBookAvailability(self, id, value):
    #     for book in self._list:
    #         if book.getID() == id:
    #             book.setAvailability(value)
    #             break

    # search for books with the desired attributes and returns them through a list
    # def searchBooks(self, criteria, stringToSearch):
    #     self._searchResults = []
    #     for book in self._list:
    #         if criteria == "id" and book.getID() == int(stringToSearch):
    #             self._searchResults.append(book)
    #         elif criteria == "title" and stringToSearch in book.getTitle().lower():
    #             self._searchResults.append(book)
    #         elif criteria == "author" and stringToSearch in book.getAuthor().lower():
    #             self._searchResults.append(book)
    #         elif criteria == "description" and stringToSearch in book.getDescription().lower():
    #             self._searchResults.append(book)
    #     return self._searchResults

    # returns a list with the books sorted in descending order by the number of rentals
    # def findMostRentedBooks(self):
    #     statistics = []
    #     for book in self._list:
    #         statistics.append([book, book.getRentalsNumber()])
    #     for i in range(len(statistics)-1):
    #         for j in range(i+1, len(statistics)):
    #             if statistics[i][1] < statistics[j][1]:
    #                 statistics[i], statistics[j] = statistics[j], statistics[i]
    #     return statistics