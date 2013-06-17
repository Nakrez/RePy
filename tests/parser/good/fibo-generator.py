def gen_fibonacci():
    a, b = 0, 1

    while True:
        yield a
        a, b = b, a + b

fi = gen_fibonacci()
for i in range(20):
    print(fi.next())
