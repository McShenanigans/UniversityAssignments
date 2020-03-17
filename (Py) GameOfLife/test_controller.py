from unittest import TestCase
from controller import Controller


class TestController(TestCase):
    def test_placeObject(self):
        cont = Controller()
        cont.placeObject("block", "1,1")
        assert (cont.table[0][0] == cont.table[1][0] == cont.table[0][1] == cont.table[1][1] == "X")
        for i in range(2,8):
            for j in range(2,8):
                assert (cont.table[i][j] == " ")

    def test_tick(self):
        cont = Controller()
        cont.placeObject("block", "1,1")
        firstTable = cont.table
        cont.tick(1)
        assert (firstTable == cont.table)