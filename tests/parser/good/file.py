my_file = open("/tmp/my_file", "w")
my_file.write("Test string")
my_file.close()

my_file = open("/tmp/my_file", "r")
content = my_file.read()
my_file.close()

if (content == "Test string"):
    print("OK")
else:
    print("KO")
