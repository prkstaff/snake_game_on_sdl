CSTD=-std=c++11 -stdlib=libc++
LIBS=classes/

all: snakegame

snakegame: libraries
	clang++ $(CSTD) main.cpp libraries/*.o -o snakegame -I/usr/local/include -L/usr/local/lib -lSDL2 -lSDL2_ttf -lSDL2_mixer

libraries:
	mkdir libraries/; exit 0
	for dir in $(LIBS); do \
		cd $$dir; \
		clang++ -I/usr/local/include $(CSTD) -c *.cpp; \
		mv *.o  ../libraries; \
		cd -; \
	done;

clean:
	rm -rf libraries/  snakegame
