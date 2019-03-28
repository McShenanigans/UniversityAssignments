import unittest
from classes.client import Client
from repositories.clientRepository import ClientRepo

class TestClientRepo(unittest.TestCase):
    # tests the addClient method
    def test_Add(self):
        repo = ClientRepo()
        repo.addClient(Client(1, "Vasi"))
        assert(len(repo.getAll()) == 1)

    # tests the removeClient method
    def test_Remove(self):
        repo = ClientRepo()
        repo.addClient(Client(1, "Vasi"))
        repo.removeClient(1)
        assert(len(repo.getAll()) == 0)

        repo.addClient(Client(1, "Vasi"))
        repo.removeClient(2)
        assert(len(repo.getAll()) == 1)

    # tests the updateClient method
    def test_Update(self):
        repo = ClientRepo()
        repo.addClient(Client(1, "Vasi"))
        repo.updateClient(1, "Vadim")
        assert(repo.getAll()[0].getName() == "Vadim")

        repo.removeClient(1)
        repo.addClient(Client(1, "Vasi"))
        repo.updateClient(2, "Vadim")
        assert(repo.getAll()[0].getName() == "Vasi")

    # tests the searchClients method
    def test_Search(self):
        repo = ClientRepo()
        client1 = Client(1, "Vasile Pushcashu")
        repo.addClient(client1)
        client2 = Client(2, "Gheorghe Bulan")
        repo.addClient(client2)
        client3 = Client(3, "Mircea Minune")
        repo.addClient(client3)
        assert(repo.searchClient("id", 5) == [])
        assert(repo.searchClient("name", "ba") == [])
        assert(repo.searchClient("id", 3) == [client3])
        assert(repo.searchClient("name", "e") == [client1, client2, client3])
        assert(repo.searchClient(15, "ba") == [])

class ClientTest(unittest.TestCase):
    # tests the updateName method
    def test_UpdateName(self):
        client = Client(1, "Vasy")
        client.updateName("Boris")
        assert(client.getName() == "Boris")

if __name__== '__main__':
    unittest.main()