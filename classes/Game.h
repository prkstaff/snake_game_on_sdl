#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>

class Game
{
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        bool game_is_running;
        SDL_Event sdl_event;
        SDL_Window* window;
        SDL_Surface* screenSurface;
        SDL_Surface* closeButton;
        enum SnakeSprites{
            SNAKE_HEAD,
            SNAKE_BODY,
            SNAKE_BODY_TURN,
            SNAKE_TAIL,
            APPLE
        };
        //SDL_Surface* loadSurface( std::string path);
        bool initSDLScreen();
        void placeExitButton();
        void processInput();
        void updateGame();
        void drawGame();
        void closeGame();
    public:
        Game(int sWidth, int sHeight);
        void run();
};

#endif /* GAME_H */
