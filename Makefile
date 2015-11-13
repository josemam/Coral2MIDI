EXE = coral
CXX = g++
TEST = ex1
PLAYER = totem salida.mid 2> /dev/null  # Reproductor por defecto de Ubuntu
#PLAYER = timidity salida.mid           # Reproductor alternativo

$(EXE) : coral.cpp voice.cpp midi.cpp
	$(CXX) -o $(EXE) $^

test : $(EXE)
	./$(EXE) < $(TEST) && $(PLAYER)

clean :
	rm -f $(EXE)
