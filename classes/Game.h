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
        int snake_sprite_square_size;
        SDL_Surface *surface;
        SDL_Texture *sprite;
        SDL_Event sdl_event;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *sprites;
        Position apple_position;
        bool ate_apple;
        std::vector <Position>  snakePositions;
        enum Directions{
            UP=0,
            RIGHT,
            DOWN,
            LEFT,
            DEFAULT,
        };
        int direction;
        int old_direction;
        enum SnakeSprites{
            SNAKE_HEAD,
            SNAKE_BODY,
            SNAKE_BODY_TURN,
            SNAKE_TAIL,
            APPLE
        };
        //SDL_Surface* loadSurface( std::string path);
        bool check_is_snake_position(int x, int y);
        void if_its_empty_move_snake(int x, int y, int direct);
        bool initSDLScreen();
        std::vector <int> get_snake_params_for_drawing(std::vector <Position> pos, size_t index);
        void processInput();
        void updateGame();
        void drawGame();
        void closeGame();
    public:
        Game(int sWidth, int sHeight);
        void run();
};

#endif /* GAME_H */
