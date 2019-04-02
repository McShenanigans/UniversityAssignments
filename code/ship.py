# class for representing a ship
class Battleship:
    def __init__(self, length, posX, posY, orientation):
        self._length = length
        self._posX = posX
        self._posY = posY
        self._orientation = orientation
        self._hits = []

    # returns the length of the ship
    @property
    def length(self):
        return self._length

    # returns the ships's coordinates
    @property
    def coordinates(self):
        coords = []
        for i in range(self._length):
            if self._orientation == "vertical":
                coords.append([self._posX, self._posY+i])
            else:
                coords.append([self._posX+i, self._posY])
        return coords

    # returns True if the ship has been destroyed and false otherwise
    @property
    def isDestroyed(self):
        return self._length == len(self._hits)

    # adds to the list of hits the coordinates at which the ship was hit
    def hit(self, x, y):
        if [x, y] not in self._hits:
            self._hits.append([x,y])