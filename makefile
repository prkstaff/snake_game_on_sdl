all: snake

snake: main.o Game.o Position.o TextDraw.o Snake.o Sound.o Command.o InputHandler.o Scene.o GameManager.o
	clang++ -std=c++11 -stdlib=libc++ main.o Game.o  Position.o TextDraw.o Snake.o Sound.o Command.o InputHandler.o Scene.o GameManager.o -o snakegame -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer

main.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c main.cpp

Game.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Game.cpp

Position.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Position.cpp

TextDraw.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/TextDraw.cpp

Snake.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Snake.cpp

Sound.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Sound.cpp

Command.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Command.cpp

InputHandler.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/InputHandler.cpp

Scene.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/Scene.cpp

GameManager.o:
	clang++ -I/usr/local/include -std=c++11 -stdlib=libc++ -c classes/GameManager.cpp


clean:
	rm *.o snakegame
