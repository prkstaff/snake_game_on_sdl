all: snake

snake: main.o Game.o Position.o TextDraw.o Snake.o Sound.o Command.o InputHandler.o
	clang++ -std=c++11 -stdlib=libc++ main.o Game.o  Position.o TextDraw.o Snake.o Sound.o Command.o InputHandler.o -o snakegame -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer

main.o:
	clang++ -std=c++11 -stdlib=libc++ -c main.cpp

Game.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/Game.cpp

Position.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/Position.cpp

TextDraw.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/TextDraw.cpp

Snake.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/Snake.cpp

Sound.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/Sound.cpp

Command.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/Command.cpp

InputHandler.o:
	clang++ -std=c++11 -stdlib=libc++ -c classes/InputHandler.cpp

clean:
	rm *.o snakegame
