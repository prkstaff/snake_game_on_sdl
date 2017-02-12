all: snake

snake: main.o Game.o Position.o TextDraw.o
	g++ main.o Game.o  Position.o TextDraw.o -o snakegame -L/usr/local/lib -lSDL2 -lSDL2_ttf

main.o:
	g++  -c main.cpp

Game.o:
	g++ -c classes/Game.cpp

Position.o:
	g++ -c classes/Position.cpp

TextDraw.o:
	g++ -c classes/TextDraw.cpp

clean:
	rm *.o snakegame
