import os

tests= []

def scale_geopositions(geopositions):
  min_lat = float(min(geopositions, key=lambda x: x[0])[0])
  max_lat = float(max(geopositions, key=lambda x: x[0])[0])
  min_lng = float(min(geopositions, key=lambda x: x[1])[1])
  max_lng = float(max(geopositions, key=lambda x: x[1])[1])
  scaled_geopositions = []
  for latitude, longitude in geopositions:
    latitude = float(latitude)
    longitude = float(longitude)
    scaled_latitude = (latitude - min_lat) / (max_lat - min_lat) * 5000
    scaled_longitude = (longitude - min_lng) / (max_lng - min_lng) * 5000
    scaled_latitude += 8000
    scaled_longitude += 8000
    if (scaled_latitude/100, scaled_longitude/100) not in scaled_geopositions:
        scaled_geopositions.append((scaled_latitude/100, scaled_longitude/100))
  return scaled_geopositions

for path in os.listdir("./test"):
    # check if current path is a file
    if os.path.isfile(os.path.join("./test", path)):
        tests.append(path)

for test in tests:
    result = ""
    geopositions = []

    with open("./test/" + test) as file:
        for line in file:
            splitted_line = line.split(",")

            geopositions.append((splitted_line[0], splitted_line[1]))

    scaled_geopositions = scale_geopositions(geopositions)

    

    with open('./test/results/'+ test[:-4] + '.txt', 'w') as f:
        for item in scaled_geopositions:
          f.write(str(int(item[0])) +" " + str(int(item[1])))
          f.write("\n")
            