from player import Player
import unittest

# tests the methods of the player class
class playerTest(unittest.TestCase):

    # tests the addShip method
    def test_addShip(self):
        player = Player()
        player.addShip(4,1,1,"vertical")
        assert(len(player.ships) == 1)

if __name__ == "__main__":
    unittest.main()