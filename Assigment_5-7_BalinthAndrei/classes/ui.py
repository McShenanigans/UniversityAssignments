class UI():
    def __init__(self):
        pass

# prints put the menu from which the user can select a command
    def mainMenu(self):
        print("\nPlease choose an action from this list:\n"
              "\t0 -> exit the program\n"
              "\t1 -> list books\n"
              "\t2 -> list clients\n"
              "\t3 -> list rentals\n"
              "\t4 -> add books to list\n"
              "\t5 -> remove a book from the list\n"
              "\t6 -> update the details of a book\n"
              "\t7 -> add client to list\n"
              "\t8 -> remove a client from the list\n"
              "\t9 -> update the details of a client\n"
              "\t10 -> rent a book to a client\n"
              "\t11 -> return a book from a client\n"
              "\t12 -> search for books\n"
              "\t13 -> search for clients\n"
              "\t14 -> show statistics for books\n"
              "\t15 -> show most active clients sorted in descending order\n"
              "\t16 -> show all the late rentals sorted in descending order\n"
              "\t17 -> undo last performed operation\n"
              "\t18 -> redo last undone operation\n")

# reads a command a returns a int in the supported range if possible and -1 otherwise
    def readCommand(self):
        command = input("\n>>> ")
        try:
            return int(command)
        except:
            return -1

# notifies user of invalid input
    def invalidInput(self):
        print("\nERROR! INVALID INPUT!\n")

# notifies user that the inputted book ID is not in the list of book IDs
    def bookNotInListUI(self):
        print("The ID you entered does not correspond to any book from the list.")

# notifies user that the selected book is not available for rent
    def bookNotAvailable(self):
        print("The book you want to rent is not available.")

# notifies user that the inputted client ID is not in the list of client IDs
    def clientNotInListUI(self):
        print("The ID you entered does not correspond to any client from the list.")

# prints out all element of a list of objects
    def listObject(self, list):
        for object in list:
            print(object)

# reads and returns the title, description and author of a new book
    def addBookUI(self):
        self._title = input("Please enter the Title of the book. ")
        self._desc = input("Please enter a description for the book. ")
        self._author = input("Please enter the name of the book's author. ")
        return self._title, self._desc, self._author

# reads a book ID and validates it, then returns the ID if it is valid or -1 otherwise
    def removeBookUI(self, bookList):
        id = input("What is the ID of the book you want to delete? ")
        try:
            for book in bookList:
                if book.getID() == int(id):
                    return int(id)
            self.bookNotInListUI()
            return -1
        except:
            self.invalidInput()
            return -1

# reads a book ID and validates it, the returns the ID if it is valid and -1 otherwise
    def updateBookID(self, bookList):
        id = input("Please enter the ID of the book you want to update. ")
        try:
            for book in bookList:
                if book.getID() == int(id):
                    return int(id)
            self.bookNotInListUI()
            return -1
        except:
            self.invalidInput()
            return -1

# reads and validates the attributes of a book that the user wants to update, returning the valid attributes
    def updateBookUI(self):
        attributes = input("Please enter the attributes you want to modify. (Title, Description, Author)").split(" ")
        if len(attributes) < 4 and len(attributes) > 0:
            for att in attributes:
                att.lower()
                if att not in ["title", "description", "author"]:
                    self.invalidInput()
                    return []
            return attributes
        print("invalid length")
        self.invalidInput()
        return []

# reads and returns the new title of a book that the user wants to update
    def updateBookTitle(self):
        return input("Please enter the new title of the book." )

# reads and returns the new description of a book that the user wants to update
    def updateBookDescription(self):
        return input("Please enter the new description of the book. ")

# reads and returns the new author of a book that the user wants to update
    def updateBookAuthor(self):
        return input("Please enter the new name of the book's author. ")

# reads and returns the name of a new client
    def addClientUI(self):
        return input("Please enter the name of the new client. ")

# reads a client ID and checks if it is in the list of client IDs, returning it as an int or -1 otherwise
    def removeClientUI(self, clientList):
        id = input("Please enter the ID of the client you want to remove. ")
        try:
            for client in clientList:
                if client.getID() == int(id):
                    return int(id)
            self.clientNotInListUI()
            return -1
        except:
            self.invalidInput()
            return -1

# reads a client ID and checks if it is in the list of client IDs, returning it as an int or -1 otherwise
    def updateClientUI(self, clientList):
        id = input("Please enter the ID of the client who's information you want to update. ")
        try:
            for client in clientList:
                if client.getID() == int(id):
                    return int(id)
            self.clientNotInListUI()
            return -1
        except:
            self.invalidInput()
            return -1

# reads the new name of a client that the user wnats to update
    def updateClientName(self):
        return input("Please enter the new name of the selected client. ")

# reads the ID of the book to be rented and the ID of the client who wants to rent the book, validating both
    def createRentalUI(self, bookList, clientList):
        self._ok = False
        bookID = input("Please enter the ID of the book you wan to rent. ")
        try:
            for book in bookList:
                if book.getID() == int(bookID):
                    if not book.getAvailability():
                        self.bookNotAvailable()
                        return -1, -1
                    self._ok = True
                    break
            if not self._ok:
                self.bookNotInListUI()
                return -1, -1
        except:
            if not self._ok:
                self.invalidInput()
                return -1, -1
        self._ok = False
        clientID = input("Please enter the ID of the client you want to rent the book to. ")
        try:
            for client in clientList:
                if client.getID() == int(clientID):
                    self._ok = True
                    break
            if not self._ok:
                self.clientNotInListUI()
                return -1, -1
        except:
            if not self._ok:
                self.invalidInput()
                return -1, -1
        return int(bookID), int(clientID)

# reads the ID of the book to be returned and the ID of the client who should have the book, validating both
    def returnBookUI(self, rentalList, bookList, clientList):
        self._ok = False
        clientID = input("Please enter the ID of the client you want to return a book from. ")
        try:
            for client in clientList:
                if client.getID() == int(clientID):
                    self._ok = True
                    break
            if not self._ok:
                self.clientNotInListUI()
                return -1, -1
        except:
            if not self._ok:
                self.invalidInput()
                return -1, -1
        self._ok = False
        bookID = input("Please enter the ID of the book you want to return. ")
        try:
            for book in bookList:
                if book.getID() == int(bookID):
                    self._ok = True
                    break
            if not self._ok:
                self.bookNotInListUI()
                return -1, -1
        except:
            if not self._ok:
                self.invalidInput()
                return -1, -1
        self._ok = False
        for rental in rentalList:
            if rental.getBookID() == int(bookID) and rental.getClientID() == int(clientID) and rental.getReturnedDate() == "":
                return int(bookID), rental
        self.bookNotAtClient()
        return -1, -1

# notifies the user that the book to be returned was not rented by the user with the inputted ID
    def bookNotAtClient(self):
        print("The book you want to return was not rented by this client.")

# manages the input for the search book function and returns it
    def searchForBookUI(self, bookManager):
        self._criteria = input("Please enter the criteria by which you want to search (id, title, description, author) ").lower()
        if self._criteria == "id":
            id = input("Please enter the ID of the book you want to search for. ")
            try:
                for book in bookManager.getAll():
                    if book.getID() == int(id):
                        return self._criteria, id
                self.bookNotInListUI()
                return ["", ""]
            except:
                pass
        elif self._criteria == "title":
            self._title = input("Please enter the title of the book you want to search for. ")
            return self._criteria, self._title
        elif self._criteria == "description":
            self._description = input("Please enter the description of the book you want to search for. ")
            return self._criteria, self._description
        elif self._criteria == "author":
            self._author = input("Please enter the name of the book's author you want to search for. ")
            return self._criteria, self._author
        self.invalidInput()
        return ["", ""]

# prints out the results of the search book function
    def printSearchBookResult(self, searchResults):
        if len(searchResults) == 0:
            self.noBookResultsFound()
        else:
            print("Here are the results:\n")
            for result in searchResults:
                print(result)

# notifies user that the book search did not return any results
    def noBookResultsFound(self):
        print("There are no books with the specified attributes in the list.")

# manages the input for the search client function and returns it
    def searchForClientUI(self, clientManager):
        self._criteria = input("Please input the criteria by which you want to search for clients (id, name)").lower()
        if self._criteria == "id":
            try:
                self._id = input("Please input the ID of the client you want to search for. ")
                for client in clientManager.getAll():
                    if client.getID() == int(self._id):
                        return self._criteria, self._id
                self.clientNotInListUI()
                return ["", ""]
            except:
                pass
        elif self._criteria == "name":
            self._name = input("Please enter the name of the client you want to search for. ")
            return self._criteria, self._name
        self.invalidInput()
        return ["", ""]

# prints out the results of the search clients function
    def printSearchClientResult(self, searchResult):
        if len(searchResult) == 0:
            self.noClientResultsFound()
        else:
            print("Here are the results:\n")
            for client in searchResult:
                print(client)

# notifies the user that the client search did not return any results
    def noClientResultsFound(self):
        print("There are no clients with the specified attributes in the list.")

# reads and returns the input for the bookStatistics function
    def bookStatisticsUI(self):
        print ("\n\t1 -> list books by number of rentals\n"
               "\t2 -> list books by number of days they were rented\n"
               "\t3 -> list most rented authors")
        return self.readCommand()

# prints out the list of most rented books
    def printBookStatistics(self, statistics):
        for stat in statistics:
            print(str(stat[0]) + "\n" + str(stat[1]) + " rentals")

# prints out the most rented authors sorted in ascending order
    def printStatistics(self, results):
        for result in results:
            print(result)

    def printException(self, e):
        print(e)