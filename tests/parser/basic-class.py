class Test:
    x = 0
    y = 0
    z = 0

    def print_x(self):
        print(self.x)

    def print_y(self):
        print(self.y)

    def print_z(self):
        print(self.z)

    def print_all(self):
        self.print_x()
        self.print_y()
        self.print_z()

var = Test()
var.print_all()
