import os
from numpy.random import seed
from numpy.random import randint

seed(123123)
n_points = [100,500,1000,5000,10000,20000,50000]

for points in n_points:

    with open('./sintetic_data/'+ str(points) +'.txt', 'w') as f:
        for i in range(0,points):
            f.write(str(randint(0,10000)) +" "+str(randint(0,10000)))
            f.write('\n')
            