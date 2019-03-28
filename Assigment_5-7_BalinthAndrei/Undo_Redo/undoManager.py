from Undo_Redo.undo_redoException import URException
from classes.book import Book
from classes.client import Client
from classes.ui import UI
from copy import deepcopy
from datetime import date, datetime
class UndoManager:
    def __init__(self):
        self._undos = []
        self._redos = []

    # saves the last action that the user performed
    def newUndo(self, operation, object, rentals = []):
        entry = {
            'op': operation,
            'obj': object,
            'rent': deepcopy(rentals)
        }
        self._undos.append(entry)
        self._redos = []

    # returns the length of the list of undos
    def getUndoLength(self):
        return len(self._undos)

    # returns the length of the list of redos
    def getRedoLength(self):
        return len(self._redos)

    # returns the type of operation that will be undone/redone
    def __getUndoOp(self, undo):
        return undo['op']

    # returns the object that was modified in an operation
    def __getUndoObj(self, undo):
        return undo['obj']

    # returns the list of rentals that were affected by an operation
    def __getUndoRent(self, undo):
        return undo['rent']

    # creates a list of the rentals that were affected by an undo/redo operation
    def __addUndoRent(self, undo, rent):
        undo['rent'].append(deepcopy(rent))

    def __resetUndoRent(self, undo):
        undo['rent'] = []

    # applies the undo operation
    def applyUndo(self, bookManager, clientManager, rentalManager):
        try:
            if len(self._undos) == 0:
                raise URException("There are no changes to undo.")
            command = self.__getUndoOp(self._undos[-1]).split(" ")
            if command[0] == "add":
                if command[1] == "book":
                    bookManager.removeBook(self.__getUndoObj(self._undos[-1]).getID())
                elif command[1] == "client":
                    clientManager.removeClient(self.__getUndoObj(self._undos[-1]).getID())
                self.deleteLastUndo()
            elif command[0] == "remove":
                if command[1] == "book":
                    bookManager.addBook(self.__getUndoObj(self._undos[-1]))
                    for rental in self.__getUndoRent(self._undos[-1]):
                        rentalManager.addRental(rental)
                        if rental.getReturnedDate() == "":
                            for book in bookManager.getAll():
                                if book.getID() == rental.getBookID():
                                    book.setAvailability(False)
                                    break
                elif command[1] == "client":
                    clientManager.addClient(self.__getUndoObj(self._undos[-1]))
                    for rental in self.__getUndoRent(self._undos[-1]):
                        rentalManager.addRental(rental)
                        if rental.getReturnedDate() == "":
                            for book in bookManager.getAll():
                                if book.getID() == rental.getBookID():
                                    book.setAvailability(False)
                                    break
                self.__resetUndoRent(self._undos[-1])
                self.deleteLastUndo()
            elif command[0] == "modify":
                if command[1] == "book":
                    for book in bookManager.getAll():
                        if book.getID() == self.__getUndoObj(self._undos[-1]).getID():
                            swapBook = Book(book.getID(), book.getTitle(), book.getDescription(), book.getAuthor())
                            book.updateTitle(self.__getUndoObj(self._undos[-1]).getTitle())
                            book.updateAuthor(self.__getUndoObj(self._undos[-1]).getAuthor())
                            book.updateDescription(self.__getUndoObj(self._undos[-1]).getDescription())
                            self.__getUndoObj(self._undos[-1]).updateTitle(swapBook.getTitle())
                            self.__getUndoObj(self._undos[-1]).updateDescription(swapBook.getDescription())
                            self.__getUndoObj(self._undos[-1]).updateAuthor(swapBook.getAuthor())
                            break
                elif command[1] == "client":
                    for client in clientManager.getAll():
                        if client.getID() == self.__getUndoObj(self._undos[-1]).getID():
                            swapClient = Client(client.getID(), client.getName())
                            client.updateName(self.__getUndoObj(self._undos[-1]).getName())
                            self.__getUndoObj(self._undos[-1]).updateName(swapClient.getName())
                            break
                self.deleteLastUndo()
            elif command[0] == "rent":
                self.__resetUndoRent(self._undos[-1])
                for book in bookManager.getAll():
                    if book.getID() == self.__getUndoObj(self._undos[-1]).getBookID():
                        book.setAvailability(True)
                        break
                for rental in rentalManager.getAll():
                    if rental.getID() == self.__getUndoObj(self._undos[-1]).getID():
                        self.__addUndoRent(self._undos[-1], rental)
                        rentalManager.removeRental(id=rental.getID())
                        break
                self.deleteLastUndo()
            elif command[0] == "return":
                for rental in rentalManager.getAll():
                    if rental.getID() == self.__getUndoObj(self._undos[-1]).getID():
                        self.__addUndoRent(self._undos[-1], rental)
                        rental.setReturnedDate("")
                        for book in bookManager.getAll():
                            if book.getID() == rental.getBookID():
                                book.setAvailability(False)
                                break
                        # self._undos[-1].setReturnedDate(self.__getUndoRent(self._undos[-1])[0].getReturnedDate)
                        break
                self.deleteLastUndo()
        except URException as e:
            UI().printException(e)

    # applies the redo operation
    def applyRedo(self, bookManager, clientManager, rentalManager):
        try:
            if len(self._redos) == 0:
                raise URException("There are no undos to redo.")
            command = self.__getUndoOp(self._redos[-1]).split(" ")
            if command[0] == "add":
                if command[1] == "book":
                    bookManager.addBook(self.__getUndoObj(self._redos[-1]))
                elif command[1] == "client":
                    clientManager.addClient(self.__getUndoObj(self._redos[-1]))
                self.deleteLastRedo()
            elif command[0] == "remove":
                if command[1] == "book":
                    bookManager.removeBook(self.__getUndoObj(self._redos[-1]).getID())
                    for rental in rentalManager.getAll():
                        if rental.getBookID() == self.__getUndoObj(self._redos[-1]).getID():
                            self.__addUndoRent(self._redos[-1], rental)
                            rentalManager.removeRental(id=rental.getID())
                elif command[1] == "client":
                    clientManager.removeClient(self.__getUndoObj(self._redos[-1]).getID())
                    for rental in rentalManager.getAll():
                        if rental.getClientID() == self.__getUndoObj(self._redos[-1]).getID():
                            self.__addUndoRent(self._redos[-1], rental)
                            rentalManager.removeRental(clientID=self.__getUndoObj(self._redos[-1]).getID(), bookList=bookManager.getAll())
                self.deleteLastRedo()
            elif command[0] == "modify":
                if command[1] == "book":
                    for book in bookManager.getAll():
                        if book.getID() == self.__getUndoObj(self._redos[-1]).getID():
                            swapBook = Book(book.getID(), book.getTitle(), book.getDescription(), book.getAuthor())
                            book.updateTitle(self.__getUndoObj(self._redos[-1]).getTitle())
                            book.updateAuthor(self.__getUndoObj(self._redos[-1]).getAuthor())
                            book.updateDescription(self.__getUndoObj(self._redos[-1]).getDescription())
                            self.__getUndoObj(self._redos[-1]).updateTitle(swapBook.getTitle())
                            self.__getUndoObj(self._redos[-1]).updateDescription(swapBook.getDescription())
                            self.__getUndoObj(self._redos[-1]).updateAuthor(swapBook.getAuthor())
                            break
                elif command[1] == "client":
                    for client in clientManager.getAll():
                        if client.getID() == self.__getUndoObj(self._redos[-1]).getID():
                            swapClient = Client(client.getID(), client.getName())
                            client.updateName(self.__getUndoObj(self._redos[-1]).getName())
                            self.__getUndoObj(self._redos[-1]).updateName(swapClient.getName())
                            break
                self.deleteLastRedo()
            elif command[0] == "rent":
                for book in bookManager.getAll():
                    if book.getID() == self.__getUndoObj(self._redos[-1]).getBookID():
                        book.setAvailability(False)
                        break
                for rental in self.__getUndoRent(self._redos[-1]):
                    rentalManager.addRental(rental)
                self.deleteLastRedo()
            elif command[0] == "return":
                for rental in self.__getUndoRent(self._redos[-1]):
                    for rental1 in rentalManager.getAll():
                        if rental1.getID() == rental.getID():
                            rental1.setReturnedDate(datetime.strptime(rental.getReturnedDate(), '%Y-%m-%d').date())
                            bookManager.updateBookAvailability(rental.getBookID(), True)
                            break
                self.deleteLastRedo()
        except URException as e:
            UI().printException(e)

    # handles the finalization of an undo operation
    def deleteLastUndo(self):
        newOps = []
        for i in range(len(self._undos) - 1):
            newOps.append(self._undos[i])
        self._redos.append(self._undos[-1])
        self._undos = newOps

    # handles the finalization of an redo operation
    def deleteLastRedo(self):
        newOps = []
        for i in range(len(self._redos) - 1):
            newOps.append(self._redos[i])
        self._undos.append(self._redos[-1])
        self._redos = newOps