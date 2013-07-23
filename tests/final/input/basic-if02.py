def iffun(test, second):
    if test:
        print("First Test TRUE!")
    elif second:
        print("Second Test TRUE!")
    else:
        print("All False!")

iffun(True, True)
iffun(True, False)
iffun(False, True)
iffun(False, False)
