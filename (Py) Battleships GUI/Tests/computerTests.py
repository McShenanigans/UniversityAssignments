import unittest
from table import Table
from ship import Battleship
from computer import ComputerPlayer

# tests the methods in of the computer class
class computerTests(unittest.TestCase):

    # tests the fits method
    def test_fits(self):
        comp = ComputerPlayer()
        result = comp.fits(4)
        if result[2] == "vertical":
            assert (result[1] + 4 < 8)
        elif result[2] == "horizontal":
            assert (result[0] + 4< 8)
        else:
            assert (result[0] + 4 < 8)
            assert (result[1] + 4 < 8)

    # tests the makeMove method
    def test_makeMove(self):
        comp = ComputerPlayer()
        table = Table([])
        table.table[1][1] = "O"
        table.table[2][2] = "~"
        table.table[3][3] = "O"
        results = comp.makeMove(table.table)
        assert (results not in [[1, 1], [2, 2], [3, 3]])

    # tests the findAttackCoordinates method
    def test_findAttackCoordinates(self):
        comp = ComputerPlayer()
        table = Table([])
        table.table[1][1] = "O"
        table.table[2][2] = "~"
        table.table[3][3] = "O"
        results = comp._findAttackCoordinates(table.table, 1, 1)
        assert (results == [[2,1], [3,1], [4,1], [5,1], [1,2], [1,3], [1,4], [1,5]])
        table.table[1][2] = "O"
        results = comp._findAttackCoordinates(table.table, 1, 1)
        assert (results == [[3, 1], [4, 1], [5, 1], [6, 1]])
        table.table[1][3] = "~"
        results = comp._findAttackCoordinates(table.table, 1, 1)
        assert (results == [[0,1]])

    # tests the countIntersections method
    def test_countIntersections(self):
        comp = ComputerPlayer()
        ships=[Battleship(4, 0, 0, "vertical")]
        intersections = comp.countIntersections(0, 0, 1, 0, ships)
        assert (intersections == 0)
        intersections = comp.countIntersections(0, 0, 0, 1, ships)
        assert (intersections == 1)

    # tests the setupShips method
    def test_setupShips(self):
        comp = ComputerPlayer()
        assert (len(comp.ships) == 3)

if __name__ == "__main__":
    unittest.main()