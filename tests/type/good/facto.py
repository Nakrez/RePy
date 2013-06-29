def facto(x):
    if x > 1:
        return x * facto(x - 1)
    else:
        return 1

facto(12)
