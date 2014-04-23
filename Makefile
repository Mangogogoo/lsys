CXX=g++
CXXFLAGS=-O3 -Wall 

all:
	$(CXX) $(CXXFLAGS) main.cpp -o lsys -lGL -lGLU -lglut
clean:
	rm -rf core.* lsys
