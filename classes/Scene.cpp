#include "Scene.h"
#include "Game.h"

Scene::~Scene(){
}
MainTitleScene::MainTitleScene(SDL_Renderer* therenderer){
    renderer = therenderer;
    SDL_Surface* main_title_bg_surface = SDL_LoadBMP("src/main_intro.bmp");
    if(main_title_bg_surface == NULL){
        printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
    }
    main_title_bg_texture = SDL_CreateTextureFromSurface(renderer, main_title_bg_surface);
    if(main_title_bg_texture == NULL){
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(main_title_bg_surface);
}
void MainTitleScene::draw(){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, main_title_bg_texture, NULL, &rect);
    SDL_RenderPresent(renderer);
}

MainTitleScene::~MainTitleScene(){
    SDL_DestroyTexture(main_title_bg_texture);
}

Level1Scene::Level1Scene(SDL_Renderer* therenderer){
    renderer = therenderer;
    SDL_Surface *grass_surface = SDL_LoadBMP("src/grass.bmp");
    if(grass_surface == NULL){
        printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
    }
    grass_texture = SDL_CreateTextureFromSurface(renderer, grass_surface);
    if (grass_texture == NULL) {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(grass_surface);
    grass_surface = nullptr;
};
void Level1Scene::draw(){
    printf("Ta caindo i");
    SDL_Rect grass_rect;
    grass_rect.x = 0;
    grass_rect.y = 0;
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    grass_rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size-GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    grass_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, grass_texture, NULL, &grass_rect);
    //SDL_RenderPresent(renderer);
}
Level1Scene::~Level1Scene(){
    SDL_DestroyTexture(grass_texture);
    grass_texture = nullptr;
}
