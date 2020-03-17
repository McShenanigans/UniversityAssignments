# class for reading input and showing messages via the command interface
class UI:
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

    # reads and validates the user's input during main game. Returns it if valid
    def readMove(self, a, b):
        move = input("ENTER COORDINATE TO ATTACK> ")
        if len(move) != 2:
            self.invalidAttackInput()
            return []
        if move[0] not in "12345678":
            if move[0] not in "abcdefghABCDEFGH":
                self.invalidAttackInput()
                return []
            if move[1] not in "12345678":
                self.invalidAttackInput()
                return []
            return [self._atnc[move[0].upper()], int(move[1])-1]
        if move[1] not in "abcdefghABCDEFGH":
            self.invalidAttackInput()
            return []
        return [self._atnc[move[1].upper()], int(move[0])-1]

    # sets up the player's ships and returns them
    def setupPlayer(self):
        ships = []
        ships.append(self.readShip("battleship", "4", ships))
        ships.append(self.readShip("cruiser", "3", ships))
        ships.append(self.readShip("destroyer", "2", ships))
        return ships

    # returns the attributes of a ship only when all are valid
    def readShip(self, type, len, ships):
        coordinates = []
        while coordinates == []:
            coordinates = self.readCoords(type, len, ships)
        return coordinates

    # reads and validates the user's input during the placement phase. Returns the input if valid
    def readCoords(self, type, len, ships):
        print("Enter the coordinates for your " + type + "(length = " + len + " squares):")
        x = input("Position on X axis (A -> H): ")
        if x not in "abcdefghABCDEFGH":
            self.InvalidSetupInput(type, "position on x")
            return []
        x = self._atnc[x.upper()]
        y = input("Position on Y axis (1 -> 8): ")
        if y not in "12345678":
            self.InvalidSetupInput(type, "position on y")
            return []
        y = int(y)-1
        o = input("Orientation(vertical/horizontal): ")
        o = o.lower()
        if o not in ["vertical", "horizontal"]:
            self.InvalidSetupInput(type, "orientation")
            return []
        if o == "vertical" and y + int(len) > 7 or o == "horizontal" and x + int(len) > 7:
            self.shipOutOfBounds()
            return []
        if o == "vertical":
            for ship in ships:
                coords = []
                for i in range(ship[3]):
                    if ship[2] == "vertical":
                        coords.append([ship[0], ship[1] + i])
                    else:
                        coords.append([ship[0] + i, ship[1]])
                for i in range(int(len)):
                    if [x, y + i] in coords:
                        self.ShipOverlap()
                        return []
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
                        self.ShipOverlap()
                        return []
        return [x, y, o, int(len)]

    # prints out the game's two tables
    def printTables(self, playerTable, computerTable):
        print("Your board:\n")
        print(playerTable)
        print("\nEnemy's board:\n")
        print(computerTable)

    # Prints out the game's winner
    def endGame(self, winner):
        print(winner + " won!")

    # notifies user of invalid input during placement phase
    def InvalidSetupInput(self, type, coordinate):
        print("\nINVALID " + coordinate.upper() + " for " + type + ". Please input again.\n")

    # notifies the user that last inputted ship is out of bounds
    def shipOutOfBounds(self):
        print("\nTHE SHIP IS OUT OF BOUNDS. PLEASE ENTER THE COORDINATES AGAIN.\n")

    # notifies user that last inputted ship overlaps another
    def ShipOverlap(self):
        print("\nINVALID COORDINATE! TWO SHIPS ARE OVERLAPPING!\n")

    # notifies user that the input during main game is invalid
    def invalidAttackInput(self):
        print("\nINVALID COORDINATE! YOU LOST THIS TURN.\n")