CXX=g++
RELFLAGS=-O3 -Wall -std=c++11 
DBGFLAGS=-O0 -g -Wall -pedantic -std=c++11 

debug:	
	$(CXX) $(DBGFLAGS) main.cpp -o lsys -lGL -lGLU -lglut
release:
	$(CXX) $(RELFLAGS) main.cpp -o lsys -lGL -lGLU -lglut
clean:
	rm -rf core.* lsys
