from tkinter import *
from GUIcompenents.GUIcontroller import controller

# main GUI for the GUI mode
class guiGame:
    def __init__(self):
        self._controller = controller()
        self._top = Tk()
        self._top.title("Battleships")
        self._coordinateIn = Text(self._top, height="1", width="5")
        [self._plTable, self._cpTable] = self._controller.tables
        self._playerBoard = Label(self._top, text=str(self._plTable), justify=LEFT, bg="gray", fg="white",
                            font=("Courier", "16"))
        self._compBoard = Label(self._top, text=str(self._cpTable), justify=LEFT, bg="gray", fg="white",
                          font=("Courier", "16"))
        self._applyBtn = Button(self._top, text="Attack!", font=("Helvetica", "16"), command=self._readMove)
        self._buildUI()

    # initializes the GUI
    def _buildUI(self):
        lbIn = Label(self._top, font=("Helvetica", "14"), text="Enter coordinate to attack: ")
        lbPl = Label(self._top, font=("Helvetica", "20"), text="Your Board: ")
        lbCp = Label(self._top, font=("Helvetica", "20"), text="Dușman's Board: ")

        self._playerBoard.grid(column="0", row="1", padx="30", columnspan="2")
        lbPl.grid(column="0", row="0", padx="5", pady="5", columnspan="2")
        self._compBoard.grid(column="2", row="1", padx="30", columnspan="2")
        lbCp.grid(column="2", row="0", padx="5", pady="5", columnspan="2")
        lbIn.grid(column="0", row="2", padx="15", pady="15")
        self._coordinateIn.grid(column="1", row="2", padx="15", pady="15")
        self._applyBtn.grid(column="2", row="2", padx="15", pady="15")
        self._top.mainloop()

    # reads the coordinate to be attacked and gives it to the GUIcontroller. Called at button press during main game
    def _readMove(self):
        results = self._controller.applyInput(self._coordinateIn.get(1.0, END+"-1c"))
        self._playerBoard.config(text=str(results[0]))
        self._compBoard.config(text=str(results[1]))
        self._coordinateIn.delete(1.0, END)
        if results[2] in ["computer", "player"]:
            self._coordinateIn.config(state=DISABLED)
            self._applyBtn.config(text="Close", command=self._end)
            self._controller.endGame(results[2])

    # ends the GUI. Called at button press after the game is finished
    def _end(self):
        self._top.destroy()