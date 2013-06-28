def generic_add(x, y):
    def add(d, w):
        return d + w

    return add(x, y)

a = generic_add(1, 2) + 1
a = generic_add("foo ", "bar") + "foo"
