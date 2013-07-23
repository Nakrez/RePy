def fibo(max_value):
    a, b = 0, 1
    number = 0
    while b < max_value:
        print(number, " = ", b)
        a, b = b, a + b
        number += 1

fibo(1000)
