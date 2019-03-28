from repositories.clientRepository import ClientRepo

class ClientController:
    def __init__(self):
        self._repo = ClientRepo()

    # creates a new entry in the clients list
    def addClient(self, client):
        self._repo.addClient(client)

    # removes an entry from the clients list
    def removeClient(self, id):
        self._repo.removeClient(id)

    # returns the list of clients
    def getAll(self):
        return self._repo.getAll()

    # updates the name of the client with an given ID
    def updateClient(self, id, newName):
        for client in self._repo.getAll():
            if client.getID() == id:
                client.updateName(newName)
                break

    # searches the list of clients for the ones with the desired attributes and returns a list of these clients
    def searchClient(self, criteria, stringToSearch):
        self._searchResults = []
        for client in self._repo.getAll():
            if criteria == "id" and client.getID() == int(stringToSearch):
                self._searchResults.append(client)
            elif criteria == "name" and stringToSearch in client.getName().lower():
                self._searchResults.append(client)
        return self._searchResults