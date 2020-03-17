from tkinter import *

# class for showing various messages via a GUI
class Prompt:
    def __init__(self, title, msg):
        self._top = Tk()
        self._top.title(title)
        msg = Label(self._top, font=("Helvetica", "14"), text=msg)
        msg.grid(padx="15", pady="15", row="0", column="0")
        btn = Button(self._top, text="OK", font=("Helvetica", "12"), command=self._done)
        btn.grid(padx="15", pady="15", row="1", column="0")
        self._top.mainloop()

    # called at button press. Ends the GUI
    def _done(self):
        self._top.destroy()