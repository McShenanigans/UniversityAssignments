import unittest
from datetime import date, timedelta
from classes.ui import UI
from classes.book import Book
from classes.client import Client
from classes.rental import Rental
from repositories.bookRepository import BookRepo
from repositories.clientRepository import ClientRepo
from repositories.rentalRepository import RentalRepo
from Undo_Redo.undoManager import UndoManager
class testUndo(unittest.TestCase):
    # sets up the lists needed for testing
    def setup(self, bookManager, clientManager, rentalManager):
        bookManager.addBook(Book(1, "Silmarillion", "Great book.", "J.R.R. Tolkien"))
        bookManager.addBook(Book(2, "Hurin's Children", "Great book.", "J.R.R. Tolkien"))
        bookManager.addBook(Book(3, "The Hobit", "Great book.", "J.R.R. Tolkien"))
        clientManager.addClient(Client(1, "Vasile Pushcashu"))
        clientManager.addClient(Client(2, "Gheorghe Bulan"))
        clientManager.addClient(Client(3, "Mircea Minune"))
        for i in range(3):
            rentalManager.addRental(
                Rental(i + 1, bookManager.getAll()[i], clientManager.getAll()[i].getID(), date(2015, 5, 17),
                       date(2015, 5, 17) + timedelta((i + 1) * 2 - 1), date(2015, 5, 17) + timedelta(14)))

    def test_newUndo(self):
        undoManager = UndoManager()
        undoManager.newUndo("add book", Book(4,"a","b","c"))
        assert(undoManager.getUndoLength() == 1 and undoManager.getRedoLength() == 0)

    # test the undo add operation
    def test_UndoAdd(self):
        undoManager = UndoManager()
        bookManager = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManager, clientManager,rentalManager)
        newBook = Book(4,"a","b","c")
        bookManager.addBook(newBook)
        undoManager.newUndo("add book", newBook)
        undoManager.applyUndo(bookManager, clientManager, rentalManager)
        assert(len(bookManager.getAll()) == 3)
        newClient = Client(4, "Vasy")
        clientManager.addClient(newClient)
        undoManager.newUndo("add client", newClient)
        undoManager.applyUndo(bookManager, clientManager, rentalManager)
        assert(len(clientManager.getAll()) == 3)

    # test the undo remove operation
    def test_UndoRemove(self):
        undoManager = UndoManager()
        bookManger = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManger, clientManager, rentalManager)
        undoManager.newUndo("remove book", bookManger.getAll()[-1])
        bookManger.removeBook(bookManger.getAll()[-1].getID())
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(len(bookManger.getAll()) == 3 and len(rentalManager.getAll()) == 3)
        undoManager.newUndo("remove client", clientManager.getAll()[-1])
        clientManager.removeClient(clientManager.getAll()[-1].getID())
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(len(clientManager.getAll()) == 3 and len(rentalManager.getAll()) == 3)

    # test the undo modification operation
    def test_UndoModify(self):
        undoManager = UndoManager()
        bookManger = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManger, clientManager, rentalManager)
        swapObject = Book(bookManger.getAll()[-1].getID(), bookManger.getAll()[-1].getTitle(), bookManger.getAll()[-1].getDescription(), bookManger.getAll()[-1].getAuthor())
        modBook = bookManger.getAll()[-1]
        modBook.updateTitle("a")
        modBook.updateDescription("b")
        modBook.updateAuthor("c")
        undoManager.newUndo("modify book", swapObject)
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(modBook.getTitle() == swapObject.getTitle() and modBook.getAuthor() == swapObject.getAuthor() and modBook.getDescription() == swapObject.getDescription())
        swapObject = Client(clientManager.getAll()[-1].getID(), clientManager.getAll()[-1].getName())
        undoManager.newUndo("modify client", swapObject)
        clientManager.getAll()[-1].updateName("Vasy")
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(clientManager.getAll()[-1].getName() == swapObject.getName())

    # test the undo rent operation
    def test_UndoRent(self):
        undoManager = UndoManager()
        bookManger = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManger, clientManager, rentalManager)
        newRent = Rental(4, bookManger.getAll()[1], clientManager.getAll()[0].getID())
        undoManager.newUndo("rent", newRent)
        rentalManager.addRental(newRent)
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(len(rentalManager.getAll()) == 3 and bookManger.getAll()[1].getAvailability())

    # test the undo return operation
    def test_UndoReturn(self):
        undoManager = UndoManager()
        bookManger = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManger, clientManager, rentalManager)
        newRent = Rental(4, bookManger.getAll()[1], clientManager.getAll()[0].getID())
        undoManager.newUndo("return", newRent)
        rentalManager.addRental(newRent)
        rentalManager.setRentalReturnDate(newRent.getID())
        undoManager.applyUndo(bookManger,clientManager,rentalManager)
        assert(rentalManager.getAll()[-1].getReturnedDate() == "")


    # test the deleteLastUndo method
    def test_DeleteLastUndo(self):
        undoManager = UndoManager()
        bookManger = BookRepo()
        clientManager = ClientRepo()
        rentalManager = RentalRepo()
        self.setup(bookManger, clientManager, rentalManager)
        newBook = Book(4, "a", "b", "c")
        bookManger.addBook(newBook)
        undoManager.newUndo("add book", newBook)
        undoManager.applyUndo(bookManger, clientManager, rentalManager)
        assert(undoManager.getRedoLength() == 1)

if __name__ =='__main__':
    unittest.main()