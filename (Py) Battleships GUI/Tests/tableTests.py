import unittest
from table import Table
from ship import Battleship

# tests the methods of the table class
class tableTests(unittest.TestCase):

    # tests the applyMove method
    def test_applyMove(self):
        table = Table([])
        table.applyMove([1,1], [])
        assert(table.table[1][1] == "~")

    # tests the _makeShipVisible method
    def test_makeShipVisible(self):
        table = Table([])
        ship=Battleship(4, 1, 1, "vertical")
        table._makeShipVisible(ship)
        assert(table.table[1][1] == "X")
        assert(table.table[2][1] == "X")
        assert(table.table[3][1] == "X")
        assert(table.table[4][1] == "X")

if __name__ == "__main__":
    unittest.main()