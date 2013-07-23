class Class:
    def __init__(self, l):
        self.l = l

    def p(self):
        for l in self.l:
            print(l)

init=[]
test = Class(init)
init.append(1)
init.append(2)
init.append(3)
test.p()
