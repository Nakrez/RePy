class Test:
    def __init__(self, name, tel=""):
        self.name = name
        self.tel = tel

    def change(self, name, tel):
        self.name = name
        self.tel = tel

    def print(self, info):
        print(info, ":", self.name, self.tel)

    def pretty(self):
        print("======")
        self.print("Contact")
        print("======")

object = Test("Repy")
object.print("Object")
object.pretty()
