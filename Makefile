CXX=g++
RELFLAGS=-O3 -Wall 
DBGFLAGS=-O0 -g -Wall -pedantic 

debug:
	$(CXX) $(DBGFLAGS) main.cpp -o lsys -lGL -lGLU -lglut
release:
	$(CXX) $(RELFLAGS) main.cpp -o lsys -lGL -lGLU -lglut
clean:
	rm -rf core.* lsys
