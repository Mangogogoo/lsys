CXX=g++
CXXFLAGS=-std=c++11 -g -pg -O0

debug:
	$(CXX) $(CXXFLAGS) tokenizer_test.cpp -o tokenizer_test
	./tokenizer_test
	$(CXX) $(CXXFLAGS) config_test.cpp -o config_test
	./config_test
	$(CXX) $(CXXFLAGS) bbox_test.cpp -o bbox_test
	./bbox_test
	
clean:
	rm -rf config_test tokenizer_test bbox_test
	
    
	