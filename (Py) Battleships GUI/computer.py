from random import randint, choice
from ship import Battleship

# class for representing the computer player
class ComputerPlayer:
    def __init__(self):
        self._ships = []
        self._setupShips()

    # returns True if all the computer's ships are destroyed
    @property
    def hasLost(self):
        return self._ships[0].isDestroyed and self._ships[1].isDestroyed and self._ships[2].isDestroyed

    # returns the computer's list of ships
    @property
    def ships(self):
        return self._ships

    # chooses a valid coordinate to be attacked
    def makeMove(self, table):
        hitCoords = []
        for x in range(8):
            for y in range(8):
                if table[y][x] == "O":
                    hitCoords = self._findAttackCoordinates(table, x, y)
                    if hitCoords != []:
                        break
            if hitCoords != []:
                break
        if hitCoords == []:
            posX = randint(0, 7)
            posY = randint(0, 7)
            while table[posY][posX] not in ["X", " "]:
                posX = randint(0, 7)
                posY = randint(0, 7)
            return [posX, posY]
        else:
            return choice(hitCoords)

    # finds the best coordinates to attack starting from a given point. Returns a list of these coordinates
    def _findAttackCoordinates(self, table, x, y):
        possibleMoves = []; smartMoves = []; n = 4; i = 0; step = 1
        while n > 0:
            i += step
            if not -1 < x+i < 8:
                break
            if table[y][x+i] == "~":
                if step == -1:
                    break
                else:
                    i = 0
                    step = -1
            elif table[y][x+i] == "O":
                smartMoves = [1]
            else:
                possibleMoves.append([x+i, y])
                n -= 1
        if smartMoves != []:
            smartMoves = possibleMoves
            possibleMoves = []
        n = 4; i = 0; step = 1; smartMovesY = []; possibleMovesY = []
        while n > 0:
            i += step
            if not -1 < y+i < 8:
                break
            if table[y+i][x] == "~":
                if step == -1:
                    break
                else:
                    i = 0
                    step = -1
            elif table[y+i][x] == "O":
                smartMovesY = [1]
            else:
                possibleMovesY.append([x, y+i])
                n -= 1
        if smartMovesY != []:
            smartMovesY = possibleMovesY
            possibleMovesY = []
        smartMoves += smartMovesY
        possibleMoves += possibleMovesY
        # print("smartMoves:", smartMoves)
        # print("possibleMoves:", possibleMoves)
        if smartMoves != []:
            return smartMoves
        return possibleMoves

    # sets up the computer's ships
    def _setupShips(self):
        ships = []
        shipLength = 4
        while shipLength > 1:
            [posX, posY, orientation] = self.fits(shipLength)
            okay = False
            while not okay:
                coords = []
                if orientation == "vertical":
                    for i in range(0, shipLength):
                        if self.countIntersections(posX, posY, 0, i, ships) == 0:
                            coords.append([posX, posY + i])
                elif orientation == "horizontal":
                    for i in range(0, shipLength):
                        if self.countIntersections(posX, posY, i, 0, ships) == 0:
                            coords.append([posX + i, posY])
                elif orientation == "any":
                    for i in range(0, shipLength):
                        if self.countIntersections(posX, posY, 0, i, ships) == 0:
                            coords.append([posX, posY + i])
                        orientation = "vertical"
                    if len(coords) != shipLength:
                        coords = []
                        for i in range(0, shipLength):
                            if self.countIntersections(posX, posY, i, 0, ships) == 0:
                                coords.append([posX + i, posY])
                        orientation = "horizontal"
                if len(coords) == shipLength:
                    okay = True
                else:
                    [posX, posY, orientation] = self.fits(shipLength)
            compShip = Battleship(shipLength, posX, posY, orientation)
            self._ships.append(compShip)
            ships.append(compShip)
            shipLength -= 1

    # checks if a ship can be placed on the chosen coordinates
    def fits(self, shipLength):
        posX = randint(0, 7)
        posY = randint(0, 7)
        while posX + shipLength > 7 or posY + shipLength > 7:
            posX = randint(0, 7)
            posY = randint(0, 7)
        if posX + shipLength < 8 and posY + shipLength < 8:
            orientation = "any"
        elif posX + shipLength < 8:
            orientation = "horizontal"
        else:
            orientation = "vertical"
        return [posX, posY, orientation]

    # counts the number of intersections with other ships of the ship that is currently being placed
    def countIntersections(self, posX, posY, xOffset, yOffset, ships):
        intersections = 0
        for ship in ships:
            if [posX + xOffset, posY + yOffset] in ship.coordinates:
                intersections += 1
        return intersections
