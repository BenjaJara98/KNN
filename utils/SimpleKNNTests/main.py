from Point import Point
import os


initial_point = Point(3,3)
k = 4

tests= []

for path in os.listdir("./test"):
    # check if current path is a file
    if os.path.isfile(os.path.join("./test", path)):
        tests.append(path)

for test in tests:

    points = []
    result = []

    with open("./test/" + test) as file:
        for line in file:
            splitted_line = line.split(" ")
            x = int(splitted_line[0])
            y = int(splitted_line[1])
            points.append(Point(x,y))


    points.sort(key=lambda x: x.distance(initial_point))

    possible_points = k
    i = 0

    while i < possible_points:
        result.append(points[i])

        if(i+1 == len(points)):
            break

        if(i >= k - 1 and points[i].distance(initial_point) == points[i+1].distance(initial_point)):
            possible_points += 1
        i +=1

    with open('./test/results/'+ test[:-4] +'_solution.txt', 'w') as f:
        for r in result:
            f.write(str(r.x) +" "+str(r.y))
            f.write('\n')
            