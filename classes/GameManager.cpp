#include "GameManager.h"
#include <iostream>
#include "Game.h"

const int GameManager::SCORE_BOARD_WIDTH = 4;
int GameManager::current_animation_frame = 0;
int GameManager::snake_sprite_square_size = 60;
int GameManager::game_score = 0;
int GameManager::apples_ate = 0;
int GameManager::GAME_STATE = MAIN_SCREEN;
int GameManager::movements_made = 0;
bool GameManager::game_is_running = true;
Uint32 GameManager::MS_PER_FRAME = 1000 / 60; //FPS
GameManager* GameManager::manager_ = 0;
int GameManager::SCREEN_WIDTH = 19;
int GameManager::SCREEN_HEIGHT = 12;
GameManager* GameManager::instance(){
    if(manager_ == NULL){
        manager_ = new GameManager();
    }
    return manager_;
};
int GameManager::get_SCREEN_WIDTH(){
    return SCREEN_WIDTH;
}
void GameManager::set_SCREEN_WIDTH(int screen_width){
    SCREEN_WIDTH = screen_width;
}
int GameManager::get_SCREEN_HEIGHT(){
    return SCREEN_HEIGHT;
}
void GameManager::set_SCREEN_HEIGHT(int screen_height){
    SCREEN_WIDTH = screen_height;
}
GameManager::~GameManager(){
};
int GameManager::get_apples_ate(){
    return apples_ate;
};
void GameManager::set_apples_ate(int ates ){
    apples_ate = ates;
};
int GameManager::get_SCORE_BOARD_WIDTH(){
    return SCORE_BOARD_WIDTH;
};
int GameManager::get_game_score(){
    return game_score;
};
void GameManager::set_game_score(int score){
    game_score = score;
};
int GameManager::get_ms_per_frame(){
    return MS_PER_FRAME;
};
void GameManager::set_movements_made(int movements){
    movements_made = movements;
};
void GameManager::set_game_is_running(bool state){
    game_is_running = state;
};
int GameManager::get_movements_made(){
    return movements_made;
};
bool GameManager::get_game_is_running(){
    return game_is_running;
};
void GameManager::set_game_state(int state){
    GAME_STATE = state;
};
int GameManager::get_game_state(){
    return GAME_STATE;
};
int GameManager::get_snake_sprite_square_size(){
    return snake_sprite_square_size;
};
void GameManager::set_snake_sprite_square_size(int size){
    snake_sprite_square_size = size;
};
int GameManager::get_game_sprite_width(){
    return snake_sprite_square_size;
};
int GameManager::get_game_sprite_height(){
    return snake_sprite_square_size;
};
void GameManager::update_animation_frame(){
    if(current_animation_frame >= 59){
        current_animation_frame = 0;
    }else{
        current_animation_frame = current_animation_frame +1;
    }
}
int GameManager::get_animation_frame(){
    return current_animation_frame;
}
