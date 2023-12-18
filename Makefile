CPP=g++
OBJECTS=libs/basic.o libs/bitrankw32int.o libs/kTree.o libs/Count.o libs/knnpq.o libs/knnir.o libs/knnirBeta.o
BINS=getKNNPQ getKNNIR generateKtFromPointList getTimeKNNIR getTimeKNNPQ getKNNIRBeta getTimeKNNIRBeta getKNNIRBeta
CPPFLAGS=-std=c++11 -O3 -DNDEBUG
DEST=.

%.o: %.c
	$(CPP) $(CPPFLAGS) -c $< -o $@

getKNNPQ: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getKNNPQ getKNNPQ.cpp $(OBJECTS) -lm

getKNNIR: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getKNNIR getKNNIR.cpp $(OBJECTS) -lm

getKNNIRBeta: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getKNNIRBeta getKNNIRBeta.cpp $(OBJECTS) -lm

generateKtFromPointList: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/generateKtFromPointList generateKtFromPointList.cpp $(OBJECTS) -lm

getTimeKNNIR: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getTimeKNNIR getTimeKNNIR.cpp $(OBJECTS) -lm

getTimeKNNIRBeta: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getTimeKNNIRBeta getTimeKNNIRBeta.cpp $(OBJECTS) -lm

getTimeKNNPQ: $(OBJECTS)
	g++ $(CPPFLAGS) -o $(DEST)/getTimeKNNPQ getTimeKNNPQ.cpp $(OBJECTS) -lm

clean:
	rm -f $(OBJECTS) $(BINS)
	cd $(DEST); rm -f *.a $(BINS)