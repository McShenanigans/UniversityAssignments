from GUIcompenents.dataMover import Mover
from GUIcompenents.shipPlacement import CoordinateReader
from GUIcompenents.prompt import Prompt

# class for reading the user's input and notifying them
class GUIui:
    def __init__(self, table):
        self._atnc = {
            'A': 0,
            'B': 1,
            'C': 2,
            'D': 3,
            'E': 4,
            'F': 5,
            'G': 6,
            'H': 7
        }
        self._table = table

    # updates the table used for the preview in the CoordinateReader
    def _updateTable(self, ship):
        for i in range(ship[3]):
            if ship[2] == "vertical":
                self._table.table[ship[1] + i][ship[0]] = "X"
            else:
                self._table.table[ship[1]][ship[0] + i] = "X"

    # sets up the player with the necessary ships
    def setupPlayer(self):
        ships = []
        ships.append(self._readShip("battleship", "4", ships))
        self._updateTable(ships[0])
        ships.append(self._readShip("cruiser", "3", ships))
        self._updateTable(ships[1])
        ships.append(self._readShip("destroyer", "2", ships))
        return ships

    # returns the attributes of a ship and returns them when all are valid
    def _readShip(self, type, len, ships):
        coordinates = []
        while coordinates == []:
            coordinates = self._readCoords(type, len, ships)
        return coordinates

    # reads the attributes of a ship and returns them if they are valid and ship is correctly placed
    def _readCoords(self, type, len, ships):
        mover = Mover()
        CoordinateReader(type, self._table, mover)
        if not self.checkCoordinates(mover.var1):
            return []
        if not self._checkPlacement(mover.var1, mover.var2, ships, len):
            return []
        if mover.var1[0] in "12345678":
            y = int(mover.var1[0]) - 1
            x = self._atnc[mover.var1[1].upper()]
        else:
            y = int(mover.var1[1]) - 1
            x = self._atnc[mover.var1[0].upper()]
        return [x, y, mover.var2, int(len)]

    # verifies if the read coordinates are valid
    def checkCoordinates(self, move):
        if len(move) != 2:
            self._invalidCoordinates()
            return False
        if move[0] not in "12345678":
            if move[0] not in "abcdefghABCDEFGH":
                self._invalidCoordinates()
                return False
            if move[1] not in "12345678":
                self._invalidCoordinates()
                return False
            return True
        if move[1] not in "abcdefghABCDEFGH":
            self._invalidCoordinates()
            return False
        return True

    # verifies if a ship is correctly placed
    def _checkPlacement(self, move, orientation, ships, len):
        if orientation.lower() not in ["vertical", "horizontal"]:
            self._invalidSetupInput("orientation")
            return False
        if move[0] in "12345678":
            y = int(move[0]) - 1
            x = self._atnc[move[1].upper()]
        else:
            y = int(move[1]) - 1
            x = self._atnc[move[0].upper()]
        if orientation == "vertical":
            for ship in ships:
                coords = []
                for i in range(ship[3]):
                    if ship[2] == "vertical":
                        coords.append([ship[0], ship[1] + i])
                    else:
                        coords.append([ship[0] + i, ship[1]])
                for i in range(int(len)):
                    if [x, y + i] in coords:
                        self._shipOverlap()
                        return False
        else:
            for ship in ships:
                coords = []
                for i in range(ship[3]):
                    if ship[2] == "vertical":
                        coords.append([ship[0], ship[1] + i])
                    else:
                        coords.append([ship[0] + i, ship[1]])
                for i in range(int(len)):
                    if [x + i, y] in coords:
                        self._shipOverlap()
                        return False
        if orientation == "vertical" and y + int(len) > 7 or orientation == "horizontal" and x + int(len) > 7:
            self._shipOutOfBounds()
            return False
        return True

    # prints out the game's winner
    def endGame(self, winner):
        Prompt("Result", winner + " won!")

    # notifies user of invalid input during placement phase
    def _invalidSetupInput(self, invalidAtt):
        Prompt("ERROR", "INVALID " + invalidAtt.upper() + "! VERTICAL OR HORIZONTAL ONLY!")

    # notifies user of invalid coordinates
    def _invalidCoordinates(self):
        Prompt("ERROR",
               "INVALID COORDINATE!\nInput must contain a character from A to H and a number from 1 to 8 with nu spaces in between")

    # notifies user that the last placed ship reaches beyond the table's bounds
    def _shipOutOfBounds(self):
        Prompt("ERROR", "THE SHIP IS OUT OF BOUNDS. PLEASE ENTER THE COORDINATES AGAIN")

    # notifies user that the last placed ship overlaps another ship
    def _shipOverlap(self):
        Prompt("ERROR", "INVALID COORDINATE! TWO SHIPS ARE OVERLAPPING!")