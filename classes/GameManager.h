#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
#include <iostream>
#include <stdint.h>
#include <stdio.h>
#include <SDL2/SDL.h>
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
class GameManager{
    private:
        static GameManager* manager_;
        const static int SCORE_BOARD_WIDTH;
        static int game_score;
        static int apples_ate;
        static int GAME_STATE;
        static int movements_made;
        static bool game_is_running;
        static Uint32 MS_PER_FRAME;
        static int SCREEN_WIDTH;
        static int SCREEN_HEIGHT;
        static int snake_sprite_square_size;
        static int current_animation_frame;
        ~GameManager();
    public:
        static GameManager* instance();
        int get_SCREEN_WIDTH();
        void set_SCREEN_WIDTH(int);
        int get_SCREEN_HEIGHT();
        void set_SCREEN_HEIGHT(int);
        int get_apples_ate();
        void set_apples_ate(int);
        int get_SCORE_BOARD_WIDTH();
        void set_SCORE_BOARD_WIDTH(int);
        int get_game_score();
        void set_game_score(int);
        bool get_game_is_running();
        void set_game_is_running(bool);
        void set_movements_made(int);
        int get_movements_made();
        void set_game_state(int);
        int get_game_state();
        int get_ms_per_frame();
        int get_snake_sprite_square_size();
        void set_snake_sprite_square_size(int);
        int get_game_sprite_width();
        int get_game_sprite_height();
        void update_animation_frame();
        int get_animation_frame();
};
#endif /* ifndef _GAMEMANAGER_
class GameManager{
    private:
        static GameManager* manager_;
    public:
        static GameManager* instance();
} */
