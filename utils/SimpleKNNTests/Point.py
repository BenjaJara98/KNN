from math import hypot

class Point():

    def __init__(self, x, y):
        self.x = x
        self.y = y

    def getX(self):
        return self.X

    def getY(self):
        return self.Y

    def distance(self, point):
        dx = self.x - point.x
        dy = self.y - point.y
        return hypot(dx,dy) 
    
    def __str__(self):
        return "("+str(self.x)+","+str(self.y)+")"
