import unittest
from classes.ui import UI
from classes.book import Book
from classes.client import Client
from classes.rental import Rental
from repositories.bookRepository import BookRepo
from repositories.clientRepository import ClientRepo
from repositories.rentalRepository import RentalRepo
class testRedo(unittest.TestCase):
    # test the redo add operation
    def test_RedoAdd(self):
        pass

    # test the redo remove operation
    def test_RedoRemove(self):
        pass

    # test the redo modification operation
    def test_RedoModify(self):
        pass

    # test the redo rent operation
    def test_RedoRent(self):
        pass

    # test the redo return operation
    def test_RedoReturn(self):
        pass

    # test the deleteLastRedo method
    def test_DeleteLastRedo(self):
        pass

if __name__ =='__main__':
    unittest.main()