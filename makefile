all: snake

snake: main.o Game.o Position.o
	g++ main.o Game.o  Position.o -o snakegame -L/usr/local/lib -lSDL2

main.o:
	g++  -c main.cpp

Game.o:
	g++ -c classes/Game.cpp

Position.o:
	g++ -c classes/Position.cpp

clean:
	rm *.o snakegame
