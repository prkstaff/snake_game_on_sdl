all: snake

snake: main.o Game.o
	g++ main.o Game.o -o snakegame -L/usr/local/lib -lSDL2

main.o:
	g++  -c main.cpp

Game.o:
	g++ -c classes/Game.cpp


clean:
	rm *.o snakegame
