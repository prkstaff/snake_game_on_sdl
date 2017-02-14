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

bool Snake::is_snake_position(int x, int y){
    int has_snake_pos = false;
    for(size_t i = 0; i< get_positions().size(); i++){
        Position pedaco = get_positions()[i];
        if(pedaco.get_x() == x && pedaco.get_y() == y){
            has_snake_pos = true;
            break;
        }
    }
    return has_snake_pos;
}
