import unittest
from repositories.bookRepository import BookRepo
from classes.book import Book

class BookRepoTest(unittest.TestCase):
    # tests the addBook method
    def test_Add(self):
        repo = BookRepo()
        repo.addBook(Book(1, "a", "b", "c"))
        assert(len(repo.getAll()) == 1)

    # tests the removeBook method
    def test_Remove(self):
        repo = BookRepo()
        repo.addBook(Book(1, "a", "b", "c"))
        repo.removeBook(1)
        assert(len(repo.getAll()) == 0)

    # tests the updateBook method
    def test_Update(self):
        repo = BookRepo()
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["title"], "d", "d", "d")
        assert(repo.getAll()[0].getTitle() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["description"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["author"], "d", "d", "d")
        assert(repo.getAll()[0].getAuthor() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["description", "title"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "d" and repo.getAll()[0].getTitle() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["description", "author"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "d" and repo.getAll()[0].getAuthor() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["title", "author"], "d", "d", "d")
        assert(repo.getAll()[0].getAuthor() == "d" and repo.getAll()[0].getTitle() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["description", "title", "author"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "d" and repo.getAll()[0].getTitle() == "d" and repo.getAll()[
            0].getAuthor() == "d")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, ["abc"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "b")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, [15, 16], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "b")

        repo.removeBook(1)
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(1, [15, "description", "abc"], "d", "d", "d")
        assert(repo.getAll()[0].getDescription() == "d" and repo.getAll()[0].getTitle() == "a")

        repo = BookRepo()
        repo.addBook(Book(1, "a", "b", "c"))
        repo.updateBook(2, ["title"], "d", "d", "d")
        assert(repo.getAll()[0].getTitle() == "a")

    # test the searchBooks method
    def test_Search(self):
        repo = BookRepo()
        book1 = Book(1, "Silmarillion", "Great book from Tolkien.", "J.R.R. Tolkien")
        repo.addBook(book1)
        book2 = Book(2, "Dune", "Great book from Herbert.", "Frank Herbert")
        repo.addBook(book2)
        book3 = Book(3, "Northern Lights", "Great book from Pullman.", "Philip Pullman")
        repo.addBook(book3)
        assert(repo.searchBooks("title", "sil") == [book1])
        assert(repo.searchBooks("author", "t") == [book1, book2])
        assert(repo.searchBooks("abc", "gtfo") == [])
        assert(repo.searchBooks("author", "abc") == [])
        assert(repo.searchBooks("title", "15") == [])
        assert(repo.searchBooks(15, "text") == [])

    # test for findMostRentedBooks method
    def test_MostRentedBooks(self):
        repo = BookRepo()
        book1 = Book(1, "Silmarillion", "Great book.", "J.R.R. Tolkien")
        repo.addBook(book1)
        book2 = Book(2, "Hurin's Children", "Great book.", "J.R.R. Tolkien")
        repo.addBook(book2)
        book3 = Book(3, "The Hobit", "Great book.", "J.R.R. Tolkien")
        repo.addBook(book3)
        book4 = Book(4, "The Lord of the Rings: The Fellowship of the Ring", "Great book.", "J.R.R. Tolkien")
        repo.addBook(book4)
        book5 = Book(5, "The Lord of the Rings: The Two Towers", "Great book.", "J.R.R. Tolkien")
        repo.addBook(book5)
        books = [book5, book4, book3, book2, book1]
        for i in range(len(repo.getAll())):
            for j in range(i):
                repo.getAll()[i].incrementRentalsNumber()
        mostWanted = repo.findMostRentedBooks()
        for i in range(5):
            assert(mostWanted[i] == [books[i], 4 - i])

class BookTest(unittest.TestCase):
    # test the setAvailability method
    def test_SetAvailability(self):
        book =(Book(1, "a", "b", "c"))
        book.setAvailability(True)
        assert(book.getAvailability() == True)
        book.setAvailability(False)
        assert(book.getAvailability() == False)

    # tests the updateTitle method
    def test_UpdateTitle(self):
        book = Book(1, "a", "b", "c")
        book.updateTitle("D")
        assert(book.getTitle() == "D")

    # tests the updateDescription method
    def test_UpdateDescription(self):
        book = Book(1, "a", "b", "c")
        book.updateDescription("D")
        assert(book.getDescription() == "D")

    # tests the updateAuthor method
    def test_UpdateAuthor(self):
        book = Book(1, "a", "b", "c")
        book.updateAuthor("D")
        assert(book.getAuthor() == "D")

    # tests the incrementRentals method
    def test_IncrementRentals(self):
        book = Book(1, "a", "b", "C")
        book.incrementRentalsNumber()
        assert(book.getRentalsNumber() == 1)

if __name__ == '__main___':
    unittest.main()