#include "Scene.h"
#include "Game.h"

Scene::~Scene(){
}
//
//http://patorjk.com/software/taag/
//██╗     ███████╗██╗   ██╗███████╗██╗          ██╗
//██║     ██╔════╝██║   ██║██╔════╝██║         ███║
//██║     █████╗  ██║   ██║█████╗  ██║         ╚██║
//██║     ██╔══╝  ╚██╗ ██╔╝██╔══╝  ██║          ██║
//███████╗███████╗ ╚████╔╝ ███████╗███████╗     ██║
//╚══════╝╚══════╝  ╚═══╝  ╚══════╝╚══════╝     ╚═

Level1Scene::Level1Scene(SDL_Renderer* therenderer){
    renderer = therenderer;
    SDL_Surface* snake_surface = SDL_LoadBMP("src/snake_apple_90x90x450.bmp");
     if(snake_surface == NULL){
        printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
     }
     SDL_SetColorKey(snake_surface, SDL_TRUE, 0xFFFFFF);
    snake_sprites = SDL_CreateTextureFromSurface(renderer, snake_surface);
    if(snake_sprites == NULL){
        printf( "sprite could not be created! SDL_Error: %s\n", SDL_GetError() );
    }else{
        SDL_FreeSurface(snake_surface);
        //Create window
    }

    sApple = new Sprite("src/sprites/badapple", renderer);
    apple_position = new Position(2,2, DOWN);
    snake = new Snake(5,2);
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
void Level1Scene::update(){
    command = input_handler.handle_input();
    if(command){
        command->execute(snake);
    }
    if(GameManager::instance()->get_game_state() == RUNNING){
        int frame  = GameManager::instance()->get_animation_frame();
        if(frame % 10 == 0){
            //move every 10 frames
            snake->move_if_empty(apple_position);
        }
    }
}
void Level1Scene::draw_objects(){
    sApple->draw_animated(apple_position->get_x(), apple_position->get_y());
};
void Level1Scene::draw_snake(){
    snake->draw(renderer, GameManager::instance()->get_snake_sprite_square_size(), snake_sprites);
};
void Level1Scene::draw_bg(){
    SDL_Rect grass_rect;
    grass_rect.x = 0;
    grass_rect.y = 0;
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    grass_rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size-GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    grass_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, grass_texture, NULL, &grass_rect);
}
Level1Scene::~Level1Scene(){
    delete(sApple);
    delete(snake);
    delete(apple_position);
    delete(command);
    SDL_DestroyTexture(grass_texture);
    SDL_DestroyTexture(snake_sprites);
    grass_texture = nullptr;
}
