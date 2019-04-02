from player import Player
from table import Table
from computer import ComputerPlayer
from GUIcompenents.GUIui import GUIui

# main controller for the GUI mode
class controller:
    def __init__(self):
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
        self._ui = GUIui(Table([]))
        self._player = Player()
        self._computer = ComputerPlayer()
        plShips = self._ui.setupPlayer()
        for ship in plShips:
            self._player.addShip(ship[3], ship[0], ship[1], ship[2])
        self._playerTable = Table(self._player.ships)
        self._computerTable = Table([])

    # returns the player table and the computer table
    @property
    def tables(self):
        return [self._playerTable, self._computerTable]

    # applies the input read from the Text widget in mainGame module if it is valid
    def applyInput(self, input):
        if self._ui.checkCoordinates(input):
            if input[0] in "12345678":
                y = int(input[0])-1
                x = self._atnc[input[1].upper()]
            else:
                y = int(input[1])-1
                x = self._atnc[input[0].upper()]
            self._computerTable.applyMove([x, y], self._computer.ships)
            if self._computer.hasLost:
                return [self._playerTable, self._computerTable, "player"]
            self._playerTable.applyMove(self._computer.makeMove(self._playerTable.table), self._player.ships)
            if self._player.hasLost:
                return [self._playerTable, self._computerTable, "computer"]
        return [self._playerTable, self._computerTable, "#rezist"]

    # calls the endGame method from the GUIui
    def endGame(self, winner):
        self._ui.endGame(winner)