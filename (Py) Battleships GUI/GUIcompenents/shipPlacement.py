from tkinter import *

# GUI for reading the input for placing the ships
class CoordinateReader:
    def __init__(self, shipToPlace, table, mover):
        self._top = Tk()
        self._top.title("Ship placer")
        self._coordIn = Text(self._top, height="1", width="20")
        self._orIn = Text(self._top, height="1", width="20")
        self._doneBtn = Button(self._top, font=("Helvetica", "14"), text="Done", command=lambda: self._done(mover))
        self._buildUI(shipToPlace, table)

    # initializes the GUI
    def _buildUI(self, shipToPlace, table):
        lbIn = Label(self._top, font=("Helvetica", "20"), text="Place your " + shipToPlace)
        lbPl = Label(self._top, font=("Helvetica", "20"), text="Your current board:")
        playerBoard = Label(self._top, text=str(table), justify=LEFT, bg="gray", fg="white", font=("Courier", "16"))
        coordlb = Label(self._top, font=("Helvetica", "14"), text="coordinate:")
        orlb = Label(self._top, font=("Helvetica", "14"), text="orientation:")
        checkLb = Label(self._top, text="", justify=LEFT, font=("Helvetica", "10"))

        details = "A " + shipToPlace + " is a ship that occupies "
        if shipToPlace == "battleship":
            details += "4 spaces.\nIt looks like this: <==>"
        elif shipToPlace == "cruiser":
            details += "3 spaces.\nIt looks like this: <=>"
        elif shipToPlace == "destroyer":
            details += "2 spaces.\nIt looks like this: <>"
        detLb = Label(self._top, font=("Helvetica", "14"), text=details)

        lbIn.grid(column="0", row="0", columnspan="3")
        lbPl.grid(column="4", row="0", columnspan="1")
        coordlb.grid(column="0", row="1")
        self._coordIn.grid(column="1", row="1")
        orlb.grid(column="0", row="2")
        self._orIn.grid(column="1", row="2")
        detLb.grid(column="0", row="3", columnspan="3", padx="15")
        checkLb.grid(column="1", row="4", columnspan="3")
        playerBoard.grid(column="4", row="1", rowspan="5", columnspan="1", padx="15", pady="15")
        self._doneBtn.grid(column="0", row="4")
        self._top.mainloop()

    # called at button press. Saves the input and ends the GUI
    def _done(self, mover):
        mover.setVar1(self._coordIn.get(1.0, END+"-1c"))
        mover.setVar2(self._orIn.get(1.0, END+"-1c"))
        self._top.destroy()