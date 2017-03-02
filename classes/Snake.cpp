#include "Snake.h"
#include "Game.h"
#include "Sound.h"
#include "GameManager.h"

Snake::Snake(int initial_x, int initial_y){
    //initial Snake
    snake_direction = DOWN;
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
std::vector <int> Snake::get_snake_params_for_drawing(std::vector <Position> pos, size_t index){
    //vector x, y, angle
        std::vector <int> vector_to_return;
        int original_sprite_size = 90;
        int x_to_return;
        int y_to_return = 0;
        int angle_to_return;
        Position pedaco = pos[index];
        //if the tail, the first pedaco
        if(index==0){
            x_to_return = SNAKE_TAIL*original_sprite_size;//sprite cut x
            Position next_pos = pos[index+1];
            if(next_pos.get_x() > pedaco.get_x()) angle_to_return = 0;//RIGHT
            if(next_pos.get_x() < pedaco.get_x()) angle_to_return = 180;//LEFT
            if(next_pos.get_y() < pedaco.get_y()) angle_to_return = 270;//UP
            if(next_pos.get_y() > pedaco.get_y()) angle_to_return = 90;//DOWN
        //if is the head
        }else if(index == pos.size()-1){
            x_to_return = SNAKE_HEAD*original_sprite_size;//sprite cut x
            if(pedaco.get_direction() == DOWN) angle_to_return = 0;
            if(pedaco.get_direction() == UP) angle_to_return = 180;
            if(pedaco.get_direction() == LEFT) angle_to_return = 90;
            if(pedaco.get_direction() == RIGHT) angle_to_return = 270;
        }else{
            Position previous_pos = pos[index-1];
            Position next_pos = pos[index+1];
            //
            //IF IT IS A TURN
            if(previous_pos.get_x() != next_pos.get_x() && previous_pos.get_y() != next_pos.get_y()){
                x_to_return = SNAKE_BODY_TURN*original_sprite_size;
                if(pedaco.get_direction() == DOWN){
                    // DOWN from left to right
                    if(previous_pos.get_x() < next_pos.get_x()){
                        angle_to_return = 270;
                    }else{
                        angle_to_return = 180;
                    }
                }else if(pedaco.get_direction() == UP){
                    //if its going to the left
                    if(previous_pos.get_x() > next_pos.get_x()){
                        angle_to_return = 90;
                    }else{
                        angle_to_return = 0;
                    }
                }else if(pedaco.get_direction() == RIGHT){
                    //IF is going up
                    if(previous_pos.get_y() > next_pos.get_y()){
                        angle_to_return = 180;
                    }else{
                        angle_to_return = 90;
                    }
                }else if(pedaco.get_direction() == LEFT){
                    //IF is going up
                    if(previous_pos.get_y() > next_pos.get_y()){
                            angle_to_return = 270;
                    }else{
                        angle_to_return = 0;
                    }
                }
            //IF ITS A BODY
            }else{
                x_to_return = SNAKE_BODY*original_sprite_size;//sprite cut x
                if(pedaco.get_direction() == RIGHT || pedaco.get_direction() == LEFT){
                    angle_to_return = 90;
                }else{
                    angle_to_return = 0;
                }
            }
        }

        //fill the vector
        vector_to_return.push_back(x_to_return);
        vector_to_return.push_back(y_to_return);
        vector_to_return.push_back(angle_to_return);

        return vector_to_return;
}
void Snake::draw(SDL_Renderer *renderer, int snake_sprite_square_size, SDL_Texture *sprite){
// Draw Snake
    for(size_t i = 0; i < get_positions().size(); i++){
        Position pedaco = get_positions()[i];
        SDL_Rect src;
        std::vector <int> my_vect = get_snake_params_for_drawing(get_positions(),i);
        src.x = my_vect[0];
        src.y = my_vect[1];
        src.w = 90;
        src.h = 90;
        SDL_Rect dest;
        dest.x = pedaco.get_x()*snake_sprite_square_size;
        dest.y = pedaco.get_y()*snake_sprite_square_size;
        dest.w = snake_sprite_square_size;//tamanho o tile da cobra para exibir
        dest.h = snake_sprite_square_size;//tamanho o tile da cobra para exibir

        SDL_RenderCopyEx(renderer, sprite, &src, &dest, my_vect[2]/* angle */, NULL, SDL_FLIP_NONE);
    }
};
int Snake::get_direction(){
    return snake_direction;
};
int Snake::get_old_direction(){
    return snake_old_direction;
}
void Snake::set_old_direction(int direction){
    snake_old_direction = direction;
}
void Snake::set_direction(int direction){
    //dont let snake go inverse direction
    int old_direction = get_old_direction();
    if((direction==RIGHT && old_direction==LEFT) || (direction==LEFT && old_direction==RIGHT))direction=old_direction;
    if((direction==DOWN && old_direction==UP) || (direction==UP && old_direction==DOWN))direction=old_direction;
    set_old_direction(direction);
    snake_direction = direction;

};
void Snake::move_if_empty(Position* apple_position){
    int direct = get_direction();
    //Todo, create eatable, apple object and move this method inside snake class
    //Create a Eatable class with a virtual ate method.
    //Each Eatable is stored in a vector of eatable.
    //Create a Eatable manager class, it will score as you eat and manage the spawn.
    //Game class check if next snake step is a eatable in the Eatable Manager class

    Position head = get_positions()[get_positions().size()-1];
    int x = head.get_x();
    int y = head.get_y();
    switch(direct){
        case DOWN:
         y = y+1;
        break;
        case UP:
         y = y-1;
        break;
        case LEFT:
         x = x-1;
        break;
        case RIGHT:
         x = x+1;
        break;
    }
    bool is_empty = true;

    bool ate_apple = false;
    //check for snake
       if(is_snake_position(x, y)){
           is_empty = false;
       }
    //check for map borders
    if(x < 0 || y < 0 || x > GameManager::instance()->get_SCREEN_WIDTH()-GameManager::instance()->get_SCORE_BOARD_WIDTH()-1 || y > GameManager::instance()->get_SCREEN_HEIGHT() -1){
        is_empty = false;
    }

    //check if is biting the apple
    if(x == apple_position->get_x() && y == apple_position->get_y()){
        int new_x;
        int new_y;
        do{
            new_x = rand() % (GameManager::instance()->get_SCREEN_WIDTH() - GameManager::instance()->get_SCORE_BOARD_WIDTH()) ;
            new_y = rand() % GameManager::instance()->get_SCREEN_HEIGHT();
        }while(is_snake_position(new_x,new_y));
        ate_apple = true;
        GameManager::instance()->set_apples_ate(GameManager::instance()->get_apples_ate() +1);
        //play chomp sound
        Sound::instance()->play_chomp_sound();
        apple_position->set_x_y(new_x,new_y);
        GameManager::instance()->set_game_score(GameManager::instance()->get_game_score()+10);
    }

    if(is_empty){
        Position newPos(x,y, direct);
        add_position(newPos);
        if(ate_apple == false){
            erase_first_position();
        }
        ate_apple = false;
        GameManager::instance()->set_movements_made(GameManager::instance()->get_movements_made()+1);
    }
    //else game over
}

