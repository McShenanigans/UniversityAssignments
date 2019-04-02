from texttable import Texttable

class Table():
    def __init__(self):
        self._table = [[" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "],
                       [" ", " ", " ", " ", " ", " ", " ", " "], [" ", " ", " ", " ", " ", " ", " ", " "]]

    @property
    def drawTable(self):
        table = Texttable()
        for row in self._table:
            table.add_row(row)
        return table.draw()

    @property
    def table(self):
        return self._table[:]

    # places the requested object on the table
    def placeObject(self, coord, obj, length):
        k = 0
        coord = coord.split(",")
        x = int(coord[0]) - 1
        y = int(coord[1]) - 1
        if x + length > 8 or y + length > 8:
            raise ValueError
        for i in range(x, x + length):
            for j in range(y, y + length):
                if obj[k].strip() == "x":
                    if self._table[i][j] == "X":
                        raise ValueError
                    else:
                        self._table[i][j] = "X"
                k += 1

    # runs the rules of the game of life a given number of times
    def tick(self, n):
        while n > 0:
            deadCells = []
            newCells = []
            for i in range(8):
                for j in range(8):
                    n1 = self._tickAugment(i, j)
                    if self._table[i][j] == "X" and (n1 > 3 or n1 < 2):
                        deadCells.append([i, j])
                    elif n1 == 3 and self._table[i][j] == " ":
                        newCells.append([i, j])
            for cell in deadCells:
                self._table[cell[0]][cell[1]] = " "
            for cell in newCells:
                self._table[cell[0]][cell[1]] = "X"
            n -= 1

    # counts the number of live cell around a certain cell
    def _tickAugment(self, i, j):
        n1 = 0
        for a in [-1, 0, 1]:
            for b in [-1, 0,1]:
                if not (a == b and b == 0):
                    try:
                        if self._table[i + a][j + b] == "X":
                            n1 += 1
                    except:
                        pass
        return n1

    def load(self, string, row):
        for j in range(8):
            self._table[row][j] = string[j]