class MyTime:
    def __init__(self, hrs=0, mins=0, secs=0):
       totalsecs = hrs*3600 + mins*60 + secs
       self.hours = totalsecs // 3600
       leftoversecs = totalsecs % 3600
       self.minutes = leftoversecs // 60
       self.seconds = leftoversecs % 60

    def incerment(self,t):
       totalsecs = self.hours * 3600 + self.minutes * 60 + self.seconds + t
       self.hours = totalsecs // 3600
       leftoversecs = totalsecs % 3600
       self.minutes = leftoversecs // 60
       self.seconds = leftoversecs % 60

    def print(self, text):
        print(text, self.hours, "h", self.minutes, "m", self.seconds, "s")


t1 = MyTime(5,5,5)
t2 = MyTime(10,10,10)
t3 = MyTime(12,12,12)

t1.print("before:")
t1.incerment(100)
t1.print("after:")
