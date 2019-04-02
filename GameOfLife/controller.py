from table import Table

class Controller():
    def __init__(self):
        self._table = Table()

    @property
    def drawTable(self):
        return self._table.drawTable

    @property
    def table(self):
        return self._table.table

    # reads the requested object from the read-only file and places it on the table
    def placeObject(self, type, coord):
        if type == "block":
            n = 2
        elif type in ["tub", "blinker"]:
            n = 3
        else:
            n = 4
        with open("cells.txt", "r") as f:
            line = [""]
            while line[0] != type:
                line = f.readline()
                line = line.split(" ", 1)
            self._table.placeObject(coord, line[1].split(" "), n)

    # applies the game of life's rules a given number of times
    def tick(self, n):
        self._table.tick(n)

    def save(self, filename):
        with open(filename, "w") as f:
            f.write(str(self._table.table))
    def load(self, filename):
        with open(filename, "r") as f:
            string = f.read()
            string1 = string.split("], [")
            row = 0
            for str in string1:
                str = str.split("', '")
                str[0] = str[0][-1]
                str[-1] = str[-1][0]
                self._table.load(str, row)
                row += 1