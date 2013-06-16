def print_me(x):
    return lambda : print(x)

print1 = print_me(1)

print1()
