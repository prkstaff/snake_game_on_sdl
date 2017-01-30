#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>

class Game
{
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        bool game_is_running;
        SDL_Window* window;
        SDL_Surface* screenSurface;
        bool initSDLScreen();
        void processInput();
        void updateGame();
        void drawGame();
        void closeGame();
    public:
        Game(int sWidth, int sHeight);
        void run();
};

#endif /* GAME_H */
