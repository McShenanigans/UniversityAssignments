class Client():
    # sets the attributes of the new client object
    def __init__(self, id, name):
        self._name = name
        self._id = id

    def __str__(self):
        return "\n" + str(self._id) + ". " + self._name

    # returns the ID of the client
    def getID(self):
        return self._id

    # updates the name of the client
    def updateName(self, newName):
        self._name = newName

    # returns the name of the client
    def getName(self):
        return self._name