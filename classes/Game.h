#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Position.h"
#include "InputHandler.h"
#include <vector>
#include "Snake.h"

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
        static const int SCREEN_WIDTH;
        static const int SCREEN_HEIGHT;
        static const int SCORE_BOARD_WIDTH;
        static bool game_is_running;
        int snake_sprite_square_size;
        static int game_score;
        static int apples_ate;
        static int movements_made;
        static Uint32 MS_PER_FRAME;//GAME FPS
        static int GAME_STATE;
        SDL_Surface *surface;
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
        int get_SCREEN_WIDTH();
        int get_SCREEN_HEIGHT();
        void set_apples_ate(int ates);
        int get_apples_ate();
        int get_SCORE_BOARD_WIDTH();
        int get_game_score();
        void set_game_score(int score);
        void set_game_is_running(bool state);
        bool get_game_is_running();
        int get_movements_made();
        void set_movements_made(int movements);
        void set_game_state(int state);
        int get_game_state();
};

#endif /* GAME_H */
