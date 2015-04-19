EXE = coral
CXX = g++

$(EXE) : coral.cpp voice.cpp midi.cpp
	$(CXX) -o $(EXE) $^

clean :
	rm -f $(EXE)
