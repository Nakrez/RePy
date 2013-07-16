def generator(a, b):
    x = "foo"
    y = "bar"
    return x + y

a = generator(1, 2)
b = generator("a", "b")
c = generator(1, "b")
d = generator("a", 2)
