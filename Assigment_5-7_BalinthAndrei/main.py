from classes.ui import UI
from classes.rental import Rental
from classes.client import Client
from classes.book import Book
from datetime import date, timedelta
from Undo_Redo.undoManager import UndoManager
from Controllers.bookController import BookController
from Controllers.clientController import ClientController
from Controllers.rentalController import RentalController

# initializes the lists of books, clients and rentals
def setup(bookManager, clientManager, rentalManager):
    # setup for books
    bookManager.addBook(Book(1, "Silmarillion", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(2, "Hurin's Children", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(3, "The Hobit", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(4, "The Lord of the Rings: The Fellowship of the Ring", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(5, "The Lord of the Rings: The Two Towers", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(6, "The Lord of the Rings: The Return of the King", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(7, "Unfinished Stories", "Great book.", "J.R.R. Tolkien"))
    bookManager.addBook(Book(8, "Dune", "Great book.", "Frank Herbert"))
    bookManager.addBook(Book(9, "Northern Lights", "Great book.", "Philip Pullman"))
    bookManager.addBook(Book(10, "The Subtle Knife", "Great book.", "Philip Pullman"))
    bookManager.addBook(Book(11, "The Amber Spyglass", "Great book.", "Philip Pullman"))
    bookManager.addBook(Book(12, "Minecraft: Ghidul Fermierului", "Get back to work.", "Mojang"))
    bookManager.addBook(Book(13, "Femei in stiinta", "Can't say a thing.", "Rachel Ignotofsky"))
    bookManager.addBook(Book(14, "Povesti de la ferma. Un purcelus pofticios", "For preschoolers only", "Nivelul 1"))
    bookManager.addBook(Book(15, "Inainteaza in varsta cu gratie", "Singles only", "Kathleen Dowling Singh"))
    bookManager.addBook(Book(16, "book16", "desc16", "auth16"))
    bookManager.addBook(Book(17, "book17", "desc17", "auth17"))
    bookManager.addBook(Book(18, "book18", "desc18", "auth18"))
    bookManager.addBook(Book(19, "book19", "desc19", "auth19"))
    bookManager.addBook(Book(20, "book20", "desc20", "auth20"))
    bookManager.addBook(Book(21, "book21", "desc21", "auth21"))
    bookManager.addBook(Book(22, "book22", "desc22", "auth22"))
    bookManager.addBook(Book(23, "book23", "desc23", "auth23"))
    bookManager.addBook(Book(24, "book24", "desc24", "auth24"))
    bookManager.addBook(Book(25, "book25", "desc25", "auth25"))
    bookManager.addBook(Book(26, "book26", "desc26", "auth26"))
    bookManager.addBook(Book(27, "book27", "desc27", "auth27"))
    bookManager.addBook(Book(28, "book28", "desc28", "auth28"))
    bookManager.addBook(Book(29, "book29", "desc29", "auth29"))
    bookManager.addBook(Book(30, "book30", "desc30", "auth30"))
    bookManager.addBook(Book(31, "book31", "desc31", "auth31"))
    bookManager.addBook(Book(32, "book32", "desc32", "auth32"))
    bookManager.addBook(Book(33, "book33", "desc33", "auth33"))
    bookManager.addBook(Book(34, "book34", "desc34", "auth34"))
    bookManager.addBook(Book(35, "book35", "desc35", "auth35"))
    bookManager.addBook(Book(36, "book36", "desc36", "auth36"))
    bookManager.addBook(Book(37, "book37", "desc37", "auth37"))
    bookManager.addBook(Book(38, "book38", "desc38", "auth38"))
    bookManager.addBook(Book(39, "book39", "desc39", "auth39"))
    bookManager.addBook(Book(40, "book40", "desc40", "auth40"))
    bookManager.addBook(Book(41, "book41", "desc41", "auth41"))
    bookManager.addBook(Book(42, "book42", "desc42", "auth42"))
    bookManager.addBook(Book(43, "book43", "desc43", "auth43"))
    bookManager.addBook(Book(44, "book44", "desc44", "auth44"))
    bookManager.addBook(Book(45, "book45", "desc45", "auth45"))
    bookManager.addBook(Book(46, "book46", "desc46", "auth46"))
    bookManager.addBook(Book(47, "book47", "desc47", "auth47"))
    bookManager.addBook(Book(48, "book48", "desc48", "auth48"))
    bookManager.addBook(Book(49, "book49", "desc49", "auth49"))
    bookManager.addBook(Book(50, "book50", "desc50", "auth50"))
    bookManager.addBook(Book(51, "book51", "desc51", "auth51"))
    bookManager.addBook(Book(52, "book52", "desc52", "auth52"))
    bookManager.addBook(Book(53, "book53", "desc53", "auth53"))
    bookManager.addBook(Book(54, "book54", "desc54", "auth54"))
    bookManager.addBook(Book(55, "book55", "desc55", "auth55"))
    bookManager.addBook(Book(56, "book56", "desc56", "auth56"))
    bookManager.addBook(Book(57, "book57", "desc57", "auth57"))
    bookManager.addBook(Book(58, "book58", "desc58", "auth58"))
    bookManager.addBook(Book(59, "book59", "desc59", "auth59"))
    bookManager.addBook(Book(60, "book60", "desc60", "auth60"))
    bookManager.addBook(Book(61, "book61", "desc61", "auth61"))
    bookManager.addBook(Book(62, "book62", "desc62", "auth62"))
    bookManager.addBook(Book(63, "book63", "desc63", "auth63"))
    bookManager.addBook(Book(64, "book64", "desc64", "auth64"))
    bookManager.addBook(Book(65, "book65", "desc65", "auth65"))
    bookManager.addBook(Book(66, "book66", "desc66", "auth66"))
    bookManager.addBook(Book(67, "book67", "desc67", "auth67"))
    bookManager.addBook(Book(68, "book68", "desc68", "auth68"))
    bookManager.addBook(Book(69, "book69", "desc69", "auth69"))
    bookManager.addBook(Book(70, "book70", "desc70", "auth70"))
    bookManager.addBook(Book(71, "book71", "desc71", "auth71"))
    bookManager.addBook(Book(72, "book72", "desc72", "auth72"))
    bookManager.addBook(Book(73, "book73", "desc73", "auth73"))
    bookManager.addBook(Book(74, "book74", "desc74", "auth74"))
    bookManager.addBook(Book(75, "book75", "desc75", "auth75"))
    bookManager.addBook(Book(76, "book76", "desc76", "auth76"))
    bookManager.addBook(Book(77, "book77", "desc77", "auth77"))
    bookManager.addBook(Book(78, "book78", "desc78", "auth78"))
    bookManager.addBook(Book(79, "book79", "desc79", "auth79"))
    bookManager.addBook(Book(80, "book80", "desc80", "auth80"))
    bookManager.addBook(Book(81, "book81", "desc81", "auth81"))
    bookManager.addBook(Book(82, "book82", "desc82", "auth82"))
    bookManager.addBook(Book(83, "book83", "desc83", "auth83"))
    bookManager.addBook(Book(84, "book84", "desc84", "auth84"))
    bookManager.addBook(Book(85, "book85", "desc85", "auth85"))
    bookManager.addBook(Book(86, "book86", "desc86", "auth86"))
    bookManager.addBook(Book(87, "book87", "desc87", "auth87"))
    bookManager.addBook(Book(88, "book88", "desc88", "auth88"))
    bookManager.addBook(Book(89, "book89", "desc89", "auth89"))
    bookManager.addBook(Book(90, "book90", "desc90", "auth90"))
    bookManager.addBook(Book(91, "book91", "desc91", "auth91"))
    bookManager.addBook(Book(92, "book92", "desc92", "auth92"))
    bookManager.addBook(Book(93, "book93", "desc93", "auth93"))
    bookManager.addBook(Book(94, "book94", "desc94", "auth94"))
    bookManager.addBook(Book(95, "book95", "desc95", "auth95"))
    bookManager.addBook(Book(96, "book96", "desc96", "auth96"))
    bookManager.addBook(Book(97, "book97", "desc97", "auth97"))
    bookManager.addBook(Book(98, "book98", "desc98", "auth98"))
    bookManager.addBook(Book(99, "book99", "desc99", "auth99"))
    bookManager.addBook(Book(100, "book100", "desc100", "auth100"))

    # setup for clients
    clientManager.addClient(Client(1, "Vasile Pushcashu"))
    clientManager.addClient(Client(2, "Gheorghe Bulan"))
    clientManager.addClient(Client(3, "Mircea Minune"))
    clientManager.addClient(Client(4, "Cristi din Banat"))
    clientManager.addClient(Client(5, "Morico Pintea"))
    clientManager.addClient(Client(6, "Boris Westernsky"))
    clientManager.addClient(Client(7, "Mark Karlx"))
    clientManager.addClient(Client(8, "Andrei Topor"))
    clientManager.addClient(Client(9, "Floarea Dinghiveci"))
    clientManager.addClient(Client(10, "Diorica Vancila"))
    clientManager.addClient(Client(11, "Vasy 1"))
    clientManager.addClient(Client(12, "Vasy 2"))
    clientManager.addClient(Client(13, "Vasy 3"))
    clientManager.addClient(Client(14, "Vasy 4"))
    clientManager.addClient(Client(15, "Vasy 5"))
    clientManager.addClient(Client(16, "Vasy 6"))
    clientManager.addClient(Client(17, "Vasy 7"))
    clientManager.addClient(Client(18, "Vasy 8"))
    clientManager.addClient(Client(19, "Vasy 9"))
    clientManager.addClient(Client(10, "Vasy 10"))
    clientManager.addClient(Client(21, "Vasy 11"))
    clientManager.addClient(Client(22, "Vasy 12"))
    clientManager.addClient(Client(23, "Vasy 13"))
    clientManager.addClient(Client(24, "Vasy 14"))
    clientManager.addClient(Client(25, "Vasy 15"))
    clientManager.addClient(Client(26, "Vasy 16"))
    clientManager.addClient(Client(27, "Vasy 17"))
    clientManager.addClient(Client(28, "Vasy 18"))
    clientManager.addClient(Client(29, "Vasy 19"))
    clientManager.addClient(Client(30, "Vasy 20"))
    clientManager.addClient(Client(31, "Vasy 21"))
    clientManager.addClient(Client(32, "Vasy 22"))
    clientManager.addClient(Client(33, "Vasy 23"))
    clientManager.addClient(Client(34, "Vasy 24"))
    clientManager.addClient(Client(35, "Vasy 25"))
    clientManager.addClient(Client(36, "Vasy 26"))
    clientManager.addClient(Client(37, "Vasy 27"))
    clientManager.addClient(Client(38, "Vasy 28"))
    clientManager.addClient(Client(39, "Vasy 29"))
    clientManager.addClient(Client(40, "Vasy 30"))
    clientManager.addClient(Client(41, "Vasy 31"))
    clientManager.addClient(Client(42, "Vasy 32"))
    clientManager.addClient(Client(43, "Vasy 33"))
    clientManager.addClient(Client(44, "Vasy 34"))
    clientManager.addClient(Client(45, "Vasy 35"))
    clientManager.addClient(Client(46, "Vasy 36"))
    clientManager.addClient(Client(47, "Vasy 90"))
    clientManager.addClient(Client(48, "Vasy 37"))
    clientManager.addClient(Client(49, "Vasy 38"))
    clientManager.addClient(Client(50, "Vasy 39"))
    clientManager.addClient(Client(51, "Vasy 40"))
    clientManager.addClient(Client(52, "Vasy 41"))
    clientManager.addClient(Client(53, "Vasy 42"))
    clientManager.addClient(Client(54, "Vasy 43"))
    clientManager.addClient(Client(55, "Vasy 44"))
    clientManager.addClient(Client(56, "Vasy 45"))
    clientManager.addClient(Client(57, "Vasy 46"))
    clientManager.addClient(Client(58, "Vasy 47"))
    clientManager.addClient(Client(59, "Vasy 48"))
    clientManager.addClient(Client(60, "Vasy 49"))
    clientManager.addClient(Client(61, "Vasy 50"))
    clientManager.addClient(Client(62, "Vasy 51"))
    clientManager.addClient(Client(63, "Vasy 52"))
    clientManager.addClient(Client(64, "Vasy 53"))
    clientManager.addClient(Client(65, "Vasy 54"))
    clientManager.addClient(Client(66, "Vasy 55"))
    clientManager.addClient(Client(67, "Vasy 56"))
    clientManager.addClient(Client(68, "Vasy 57"))
    clientManager.addClient(Client(69, "Vasy 58"))
    clientManager.addClient(Client(70, "Vasy 59"))
    clientManager.addClient(Client(71, "Vasy 60"))
    clientManager.addClient(Client(72, "Vasy 61"))
    clientManager.addClient(Client(73, "Vasy 62"))
    clientManager.addClient(Client(74, "Vasy 63"))
    clientManager.addClient(Client(75, "Vasy 64"))
    clientManager.addClient(Client(76, "Vasy 65"))
    clientManager.addClient(Client(77, "Vasy 66"))
    clientManager.addClient(Client(78, "Vasy 67"))
    clientManager.addClient(Client(79, "Vasy 68"))
    clientManager.addClient(Client(80, "Vasy 69"))
    clientManager.addClient(Client(81, "Vasy 70"))
    clientManager.addClient(Client(82, "Vasy 71"))
    clientManager.addClient(Client(83, "Vasy 72"))
    clientManager.addClient(Client(84, "Vasy 73"))
    clientManager.addClient(Client(85, "Vasy 74"))
    clientManager.addClient(Client(86, "Vasy 75"))
    clientManager.addClient(Client(87, "Vasy 89"))
    clientManager.addClient(Client(88, "Vasy 76"))
    clientManager.addClient(Client(89, "Vasy 77"))
    clientManager.addClient(Client(90, "Vasy 78"))
    clientManager.addClient(Client(91, "Vasy 79"))
    clientManager.addClient(Client(92, "Vasy 80"))
    clientManager.addClient(Client(93, "Vasy 81"))
    clientManager.addClient(Client(94, "Vasy 82"))
    clientManager.addClient(Client(95, "Vasy 83"))
    clientManager.addClient(Client(96, "Vasy 84"))
    clientManager.addClient(Client(97, "Vasy 85"))
    clientManager.addClient(Client(98, "Vasy 86"))
    clientManager.addClient(Client(99, "Vasy 87"))
    clientManager.addClient(Client(100, "Vasy 88"))

    # setup for rentals
    for i in range(10):
        rentalManager.addRental(
            Rental(i + 1, bookManager.getAll()[i], clientManager.getAll()[i].getID(), date(2015, 5, 17),
                   date(2015, 5, 17) + timedelta((i + 1) * 2 - 1), date(2015, 5, 17) + timedelta(14)))

# the segment which processes the inputted command and starts the respective function
def main():
    bookManager = BookController()
    clientManager = ClientController()
    rentalManager = RentalController()
    undoManager = UndoManager()
    setup(bookManager, clientManager, rentalManager)
    while True:
        UI().mainMenu()
        command = UI().readCommand()
        if command == 0:
            return
        elif command == 1:
            UI().listObject(bookManager.getAll())
        elif command == 2:
            UI().listObject(clientManager.getAll())
        elif command == 3:
            UI().listObject(rentalManager.getAll())
        elif command == 4:
            attributes = UI().addBookUI()
            newBook = Book(bookManager.getAll()[-1].getID() + 1, attributes[0], attributes[1], attributes[2])
            undoManager.newUndo("add book", newBook)
            bookManager.addBook(newBook)
        elif command == 5:
            id = UI().removeBookUI(bookManager.getAll())
            if id != -1:
                results = []
                for rental in rentalManager.getAll():
                    if rental.getBookID() == id:
                        results.append(rental)
                undoManager.newUndo("remove book", bookManager.searchBooks("id", str(id))[0], results)
                bookManager.removeBook(id)
                rentalManager.removeRental(bookID=id)
        elif command == 6:
            id = UI().updateBookID(bookManager.getAll())
            if id != -1:
                book = bookManager.searchBooks("id", str(id))[0]
                swapBook = Book(book.getID(), book.getTitle(), book.getDescription(), book.getAuthor())
                undoManager.newUndo("modify book", swapBook)
                bookManager.updateBook(id, UI().updateBookUI())
        elif command == 7:
            newClient = Client(clientManager.getAll()[-1].getID() + 1, UI().addClientUI())
            undoManager.newUndo("add client", newClient)
            clientManager.addClient(newClient)
        elif command == 8:
            id = UI().removeClientUI(clientManager.getAll())
            if id != -1:
                results = []
                for rental in rentalManager.getAll():
                    if rental.getClientID() == id:
                        results.append(rental)
                undoManager.newUndo("remove client", clientManager.searchClient("id", str(id))[0], results)
                clientManager.removeClient(id)
                rentalManager.removeRental(clientID=id, bookList=bookManager.getAll())
        elif command == 9:
            id = UI().updateClientUI(clientManager.getAll())
            if id != -1:
                client = clientManager.searchClient("id", str(id))[0]
                swapClient = Client(client.getID(), client.getName())
                undoManager.newUndo("modify client", swapClient)
                clientManager.updateClient(id, UI().updateClientName())
        elif command == 10:
            ids = UI().createRentalUI(bookManager.getAll(), clientManager.getAll())
            if ids[0] != -1:
                for book in bookManager.getAll():
                    if book.getID() == ids[0]:
                        newRent = Rental(rentalManager.getAll()[-1].getID() + 1, book, ids[1])
                        undoManager.newUndo("rent", newRent)
                        rentalManager.addRental(newRent)
                        break
        elif command == 11:
            ids = UI().returnBookUI(rentalManager.getAll(), bookManager.getAll(), clientManager.getAll())
            if ids[0] != -1:
                undoManager.newUndo("return", ids[1])
                bookManager.updateBookAvailability(ids[0], True)
                rentalManager.setRentalReturnDate(ids[1].getID())
        elif command == 12:
            searchCriteria = UI().searchForBookUI(bookManager)
            if searchCriteria[0] != "":
                UI().printSearchBookResult(bookManager.searchBooks(searchCriteria[0], searchCriteria[1]))
        elif command == 13:
            searchCriteria = UI().searchForClientUI(clientManager)
            if searchCriteria[0] != "":
                UI().printSearchClientResult(clientManager.searchClient(searchCriteria[0], searchCriteria[1]))
        elif command == 14:
            criteria = UI().bookStatisticsUI()
            if criteria == 1:
                UI().printBookStatistics(bookManager.findMostRentedBooks())
            elif criteria == 2:
                UI().printStatistics(rentalManager.findBooksRentedForMostDays(bookManager.getAll()))
            elif criteria == 3:
                UI().printStatistics(rentalManager.findMostRentedAuthors(bookManager.getAll()))
            else:
                UI().invalidInput()
        elif command == 15:
            UI().printStatistics(rentalManager.findMostActiveClients(clientManager.getAll()))
        elif command == 16:
            UI().printStatistics(rentalManager.findLateRentals(bookManager.getAll()))
        elif command == 17:
            undoManager.applyUndo(bookManager, clientManager, rentalManager)
        elif command == 18:
            undoManager.applyRedo(bookManager, clientManager, rentalManager)
        else:
            UI().invalidInput()

main()
