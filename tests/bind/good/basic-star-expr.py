def fun(*args):
    return args

def fun(**arg):
    return arg

def fun(*args, **arg):
    a = args
    return arg

def fun(x, *arg, y, z=1, **a):
    t = x
    b = arg
    c = y
    d = z
    e = a
    return 1
