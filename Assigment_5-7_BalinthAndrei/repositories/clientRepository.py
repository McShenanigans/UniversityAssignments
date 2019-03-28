class ClientRepo():
    # creates an empty list in which the clients will be kept
    def __init__(self):
        self._list = []

    # creates a new entry in the clients list
    def addClient(self, client):
        self._list.append(client)

    # removes an entry from the clients list
    def removeClient(self, id):
        self._list1 = []
        for client in self._list:
            if client.getID() != id:
                self._list1.append(client)
        self._list = self._list1

    # returns the list of clients
    def getAll(self):
        return self._list

    # updates the name of the client with an given ID
    # def updateClient(self, id, newName):
    #     for client in self._list:
    #         if client.getID() == id:
    #             client.updateName(newName)
    #             break

    # searches the list of clients for the ones with the desired attributes and returns a list of these clients
    # def searchClient(self, criteria, stringToSearch):
    #     self._searchResults = []
    #     for client in self._list:
    #         if criteria == "id" and client.getID() == int(stringToSearch):
    #             self._searchResults.append(client)
    #         elif criteria == "name" and stringToSearch in client.getName().lower():
    #             self._searchResults.append(client)
    #     return self._searchResults