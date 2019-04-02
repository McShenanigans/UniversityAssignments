class UI():
    def __init__(self):
        pass

    # reads and validates and returns the user's input
    def readCommand(self):
        comm = input(">>> ").lower()
        comm = comm.split(" ")
        for c in comm:
            c.strip()
        if comm[0] not in ["place", "tick", "save", "load"]:
            raise ValueError
        if comm[0] == "place":
            if len(comm) != 3:
                raise ValueError
            if comm[1] not in ["blinker", "block", "tub", "beacon", "spaceship"]:
                raise ValueError
            coords = comm[2].split(",")
            if len(coords) != 2:
                raise ValueError
            try:
                x = int(coords[1])
                y = int(coords[0])
                if not 0 < x < 9 or not 0 < y < 9:
                    raise ValueError
            except:
                raise ValueError
        elif comm[0] == "tick":
            if len(comm) == 2:
                try:
                    n = int(comm[1].strip())
                except:
                    raise ValueError
            if 1 > len(comm) or 2< len(comm):
                raise ValueError
            if len(comm) == 1:
                comm.append("1")
        elif comm[0] == "save" or comm[0] == "load":
            file = comm[1].split(".")
            if len(comm) != 2:
                raise ValueError
            if len(file) == 1:
                comm[1] += ".txt"
            elif len(file) != 2:
                raise ValueError
        return comm

    def printError(self, e):
        print("\nERROR! " + e.upper() + "!\n")

    def printTable(self, table):
        print("\n" + table)