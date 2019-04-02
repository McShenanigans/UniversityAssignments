from ship import Battleship
import unittest

# tests the methods of the ship class
class shipTests(unittest.TestCase):

    # tests the getters
    def test_Attributes(self):
        ship = Battleship(4, 1, 1, "vertical")
        assert (ship.length == 4)
        assert (ship.coordinates == [[1, 1], [1, 2], [1, 3], [1, 4]])
        assert (ship.isDestroyed is False)

    # tests the hit method
    def test_hit(self):
        ship = Battleship(4, 1, 1, "vertical")
        ship.hit(1, 1)
        ship.hit(1, 2)
        assert (ship.isDestroyed is False)
        ship.hit(1, 3)
        ship.hit(1, 4)
        assert (ship.isDestroyed is True)

if __name__ == "__main__":
    unittest.main()