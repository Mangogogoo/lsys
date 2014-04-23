CXX=g++
CXXFLAGS=-O3 -Wall 

all:
	$(CXX) $(CXXFLAGS) main.cpp -o lsys -lGL -lglu -lglut
clean:
	rm -rf core.* lsys
