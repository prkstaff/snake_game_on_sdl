#ifndef _SNAKE_
#define _SNAKE_
#include <iostream>
#include <vector>
#include "Position.h"
#include <SDL2/SDL.h>

class Snake{
    private:
        std::vector <Position>  snakePositions;
        int snake_direction;
    public:
        Snake(int initial_x, int initial_y);
        std::vector <Position> get_positions();
        void add_position(Position new_pos);
        void erase_first_position();
        bool is_snake_position(int x, int y);
        std::vector <int> get_snake_params_for_drawing(std::vector <Position> pos, size_t index);
        void draw(SDL_Renderer *renderer, int snake_sprite_square_size, SDL_Texture *sprite);
        int get_direction();
        void set_direction(int new_direction);
};
#endif /* ifndef _SNAKE_
class Snake{

}; */
