# class for transferring data between a GUI class and the GUIcontroller
class Mover:
    def __init__(self):
        self._var1 = None
        self._var2 = None
        self._var3 = None
        self._var4 = None
        self._var5 = None
        self._isModified = False

    # returns var1
    @property
    def var1(self):
        return self._var1

    # returns var2
    @property
    def var2(self):
        return self._var2

    # returns var3
    @property
    def var3(self):
        return self._var3

    # returns var4
    @property
    def var4(self):
        return self._var4

    # returns var5
    @property
    def var5(self):
        return self._var5

    # returns the value of the isModified attribute
    @property
    def isModified(self):
        return self._isModified

    # sets the value of var1 to argument
    def setVar1(self, val):
        self._var1 = val

    # sets the value of var2 to argument
    def setVar2(self, val):
        self._var2 = val

    # sets the value of var3 to argument
    def setVar3(self, val):
        self._var3 = val

    # sets the value of var4 to argument
    def setVar4(self, val):
        self._var4 = val

    # sets the value of var5 to argument
    def setVar5(self, val):
        self._var5 = val

    # sets the value of attribute isModified to argument
    def setModified(self, val):
        self._isModified = val