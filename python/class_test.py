import math

class Point:
    x_origin = 0
    y_origin = 0
    def __init__(self, x_, y_):
        self.x = x_
        self.y = y_
        self.__d = self.dist() #math.sqrt(self.x**2 + self.y**2)

    def dist(self):
        #return self.__d
        return math.sqrt(self.x**2 + self.y**2)
        
p = Point(2, 2)
#print(p.dist())
#print(p.__d)



class Point3D(Point):
    def __init__(self, x_, y_, z_):
        self.z = z_
        super().__init__(x_, y_)

    def dist(self):
        return math.sqrt(self.x**2 + self.y**2 + self.z**2)

p3 = Point3D(2, 2, 2)
#print(p3.dist())