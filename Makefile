EXE = coral
CXX = g++
TEST = ex1

ifdef SystemRoot  # Windows
	RM = del /q
	RUNEXE = $(EXE)
	EXE := $(EXE).exe
	NULL = NUL
	PLAYER = start salida.mid             # Reproductor asignado a .mid en Windows
	#PLAYER = xmplay salida.mid           # Reproductor alternativo
else
	RM = rm -f
	RUNEXE = ./$(EXE)
	NULL = /dev/null
	PLAYER = totem salida.mid 2> $(NULL)  # Reproductor por defecto de Ubuntu
	#PLAYER = timidity salida.mid         # Reproductor alternativo
endif

$(EXE) : coral.cpp voice.cpp midi.cpp
	$(CXX) -o $(EXE) $^

test : $(EXE)
	$(RUNEXE) < $(TEST) > $(NULL) && $(PLAYER)

clean :
	$(RM) $(EXE)
