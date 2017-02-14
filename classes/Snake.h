#ifndef _SNAKE_
#define _SNAKE_
#include <iostream>
#include <vector>
#include "Position.h"

class Snake{
    private:
        std::vector <Position>  snakePositions;
    public:
        Snake(int initial_x, int initial_y);
        std::vector <Position> get_positions();
        void add_position(Position new_pos);
        void erase_first_position();
};
#endif /* ifndef _SNAKE_
class Snake{

}; */
