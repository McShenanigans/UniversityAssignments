import unittest

# class for representing a game's table
class Table:
    def __init__(self, ships):
        self._table = [[" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "]]
        for ship in ships:
            self._makeShipVisible(ship)

    # provides a way to print the table
    def __str__(self):
        string = "|_|A|B|C|D|E|F|G|H |\n"
        for i in range(0, len(self._table)):
            str1 = "|"+str(i+1)+"|"
            for j in range(0, len(self._table)):
                str1+=str(self._table[i][j])+" "
            str1+="|"
            str1+="\n"
            string += str1
        string += "|_|________________|"
        return string

    # makes a given ship visible
    def _makeShipVisible(self, ship):
        for coordinate in ship.coordinates:
            self._table[coordinate[1]][coordinate[0]] = "X"

    # applies a move and makes the changes visible in the table
    def applyMove(self, coordinates, ships):
        if self._table[coordinates[1]][coordinates[0]] in [" ", "X"]:
            for ship in ships:
                if coordinates in ship.coordinates:
                    self._table[coordinates[1]][coordinates[0]] = "O"
                    ship.hit(coordinates[0], coordinates[1])
                    return
            self._table[coordinates[1]][coordinates[0]] = "~"

    # returns the object's table
    @property
    def table(self):
        return self._table