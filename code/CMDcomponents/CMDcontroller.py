from table import Table
from CMDcomponents.ui import UI
from player import Player
from computer import ComputerPlayer

# main controller for the CMD mode
class cmdGame:
    def __init__(self):
        ui = UI()
        computerPlayer = ComputerPlayer()
        player = Player()
        ships = ui.setupPlayer()
        for ship in ships:
            player.addShip(ship[3], ship[0], ship[1], ship[2])
        playerTable = Table(player.ships)
        computerTable = Table([])
        while True:
            ui.printTables(playerTable, computerTable)
            hMove = ui.readMove(playerTable, computerTable)
            if hMove != []:
                computerTable.applyMove(hMove, computerPlayer.ships)
            if computerPlayer.hasLost:
                ui.printTables(playerTable, computerTable)
                ui.endGame("PLAYER")
                return
            playerTable.applyMove(computerPlayer.makeMove(playerTable.table), player.ships)
            if player.hasLost:
                ui.printTables(playerTable, computerTable)
                ui.endGame("COMPUTER")
                return