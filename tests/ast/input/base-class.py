class Test:
    def __init__(self, name, tel):
        self.name = name
        self.tel = tel

    def change(self, name, tel):
        self.name = name
        self.tel = tel

    def p(self, info):
        print(info, ":", self.name, sel.tel)

    def pretty(self):
        print("======")
        self.p("Contact")
        print("======")

