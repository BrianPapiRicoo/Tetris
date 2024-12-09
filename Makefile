
Game: Main.cpp TetrisPartes.cpp TetrisTablero.cpp IU.cpp
	g++ Main.cpp TetrisTablero.cpp TetrisPartes.cpp IU.cpp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio -o Game


clean:
	rm -f Game