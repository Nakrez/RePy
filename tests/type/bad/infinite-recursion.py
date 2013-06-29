def gen(x, y):
    if x:
        return gen(y, x)
    else:
        return gen(x, y)

gen(1,1)
