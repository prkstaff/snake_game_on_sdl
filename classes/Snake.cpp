#include "Snake.h"
#include "Game.h"

Snake::Snake(int initial_x, int initial_y){

    //initial Snake
    Position initial_tale(initial_x,initial_y,DOWN);
    Position initial_body2(initial_x,initial_y+1,DOWN);
    Position initial_head(initial_x,initial_y+2,DOWN);
    snakePositions.push_back(initial_tale);
    snakePositions.push_back(initial_body2);
    snakePositions.push_back(initial_head);

}

std::vector <Position> Snake::get_positions(){
    return snakePositions;
}
void Snake::add_position(Position new_pos){
    snakePositions.push_back(new_pos);
}
void Snake::erase_first_position(){
    snakePositions.erase(snakePositions.begin());
};
