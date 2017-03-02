#include "GameManager.h"
#include <iostream>

GameManager* GameManager::manager_ = 0;
GameManager* GameManager::instance(){
    if(manager_ == NULL){
        manager_ = new GameManager();
    }
    return manager_;
};
int GameManager::SCREEN_WIDTH = 19;

int GameManager::get_SCREEN_WIDTH(){
    return SCREEN_WIDTH;
}
void GameManager::set_SCREEN_WIDTH(int screen_width){
    SCREEN_WIDTH = screen_width;
}
GameManager::~GameManager(){

};
