from GUIcompenents.mainGame import guiGame
from CMDcomponents.CMDcontroller import cmdGame
from GUIcompenents.prompt import Prompt

# reads the settings file and starts the game in either GUI or CMD mode
def main():
    with open("settings.settings", "r") as f:
        mode = f.readline().split("=")
    if mode[1].strip().upper() == "GUI":
        guiGame()
    elif mode[1].strip().upper() == "CMD":
        cmdGame()
    else:
        Prompt("ERROR", "INVALID UI MODE!")

main()