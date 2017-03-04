#include "Scene.h"
#include "Game.h"

Scene::~Scene(){
}
void MainTitleScene::draw(SDL_Renderer* renderer){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    SDL_Surface* main_title_bg_surface = SDL_LoadBMP("src/main_intro.bmp");
    SDL_Texture* main_title_bg= SDL_CreateTextureFromSurface(renderer, main_title_bg_surface);
    SDL_FreeSurface(main_title_bg_surface);
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, main_title_bg, NULL, &rect);
    SDL_DestroyTexture(main_title_bg);
    SDL_RenderPresent(renderer);

}
MainTitleScene::~MainTitleScene(){
}
