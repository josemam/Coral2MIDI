EXE = coral
CXX = g++

coral : coral.cpp voice.cpp midi.cpp
	$(CXX) -o $(EXE) $^

clean :
	rm -f $(EXE)
