
SOURCES = src/Main.cpp src/TetrisTablero.cpp src/TetrisPartes.cpp src/IU.cpp src/Sonido.cpp


INCLUDE_DIR = include
BIN_DIR = bin
DATA_DIR = data


OUTPUT = $(BIN_DIR)/Game


CXXFLAGS = -I$(INCLUDE_DIR) -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio


$(OUTPUT): $(SOURCES)
	mkdir -p $(BIN_DIR)
	g++ $(SOURCES) $(CXXFLAGS) -o $(OUTPUT)


clean:
	rm -f $(OUTPUT)


run: $(OUTPUT)
	cd $(BIN_DIR) && ./Game