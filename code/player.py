from ship import Battleship

# class for representing the player
class Player:
    def __init__(self):
        self._ships = []

    # adds a ship to the player's ships
    def addShip(self, len, x, y, o):
        self._ships.append(Battleship(int(len), x, y, o))

    # returns True if all the player's ships are destroyed
    @property
    def hasLost(self):
        return self._ships[0].isDestroyed and self._ships[1].isDestroyed and self._ships[2].isDestroyed

    # returns the player's list of ships
    @property
    def ships(self):
        return self._ships