class Test:
    def __init__(name, tel=""):
        self.name = name
        self.tel = tel

    def change(name, tel):
        self.name = name
        self.tel = tel

    def print(info):
        print(info, ":", self.name, self.tel)

    def pretty():
        print("======")
        self.print("Contact")
        print("======")

