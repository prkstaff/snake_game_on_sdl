#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Position.h"
#include <vector>

//26m https://www.youtube.com/watch?v=nK_sT12h22s&list=PLt1n3PgXIOdmpmI_0PTOad7W0MlyAbHod&index=2
//
class Game
{
    private:
        const int SCREEN_WIDTH;
        const int SCREEN_HEIGHT;
        bool game_is_running;
        SDL_Surface *surface;
        SDL_Texture *sprite;
        SDL_Event sdl_event;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *sprites;
        std::vector <Position>  snakePositions;
        enum Directions{
            UP=0,
            RIGHT,
            DOWN,
            LEFT
        };
        int direction;
        enum SnakeSprites{
            SNAKE_HEAD,
            SNAKE_BODY,
            SNAKE_BODY_TURN,
            SNAKE_TAIL,
            APPLE
        };
        //SDL_Surface* loadSurface( std::string path);
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
