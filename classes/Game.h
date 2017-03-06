#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Position.h"
#include "InputHandler.h"
#include <vector>
#include "Snake.h"
#include "GameManager.h"
#include "Scene.h"

//26m https://www.youtube.com/watch?v=nK_sT12h22s&list=PLt1n3PgXIOdmpmI_0PTOad7W0MlyAbHod&index=2
//
enum Directions{
    UP=0,
    RIGHT,
    DOWN,
    LEFT,
    DEFAULT,
};
enum SnakeSprites{
    SNAKE_HEAD,
    SNAKE_BODY,
    SNAKE_BODY_TURN,
    SNAKE_TAIL,
    APPLE
};
enum GameStates{
    MAIN_SCREEN = 0,
    PAUSED,
    RUNNING
};
class Game
{
    private:
        SDL_Surface *surface;
        Scene* level_one = 0;
        SDL_Texture *sprite;
        SDL_Event sdl_event;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *sprites;
        Position apple_position;
        Snake snake;
        InputHandler input_handler;
        //SDL_Surface* loadSurface( std::string path);
        bool check_is_snake_position(int x, int y);
        bool initSDLScreen();
        void processInput();
        void updateGame();
        void draw_main_screen();
        void drawGame();
        void closeGame();
    public:
        Game();
        void run();
};

#endif /* GAME_H */
