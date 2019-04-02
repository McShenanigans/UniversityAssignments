from ui import UI
from controller import Controller

def main():
    controller = Controller()
    ui = UI()
    while True:
        ui.printTable(controller.drawTable)
        try:
            comm = ui.readCommand()
            if comm[0] == "place":
                try:
                    controller.placeObject(comm[1], comm[2])
                except:
                    ui.printError("object out of bounds or live cells overlap")
            elif comm[0] == "tick":
                controller.tick(int(comm[1]))
            elif comm[0] == "save":
                controller.save(comm[1])
            elif comm[0] == "load":
                controller.load(comm[1])
        except:
             ui.printError("invalid input")

main()
