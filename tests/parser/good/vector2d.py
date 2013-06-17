class Vector2D:
    def __init__(self, x, y):
        self.coords = (x, y)

    def __add__(self, other):
        return Vector2D(self.coords[0]+other.coords[0], self.coords[1]+other.coords[1])

    def __repr__(self):
        return "Vector2D(%s, %s)" %self.coords

a = Vector2D(1, 2)
b = Vector2D(3, 4)
print(a + b) # Vector2D(4, 6)
