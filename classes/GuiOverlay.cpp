#include "GuiOverlay.h"
#include <SDL2/SDL_ttf.h>

GuiOverlay::GuiOverlay(SDL_Renderer* therenderer){
    renderer = therenderer;
    SDL_Surface* main_title_bg_surface = SDL_LoadBMP("src/main_intro.bmp");
    textmanager = new TextDraw("src/kongtext.ttf", 24);
    if(main_title_bg_surface == NULL){
        printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
    }
    main_title_bg_texture = SDL_CreateTextureFromSurface(renderer, main_title_bg_surface);
    if(main_title_bg_texture == NULL){
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
    }
    SDL_FreeSurface(main_title_bg_surface);
};
void GuiOverlay::draw(){
    int game_state = GameManager::instance()->get_game_state();
    if( game_state == MAIN_SCREEN){
        draw_main_title();
    }else if(game_state == RUNNING){
        draw_scoreboard();
    }else if(game_state == PAUSED){
        draw_scoreboard();
        draw_pause_screen();
    }
}
void GuiOverlay::draw_main_title(){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, main_title_bg_texture, NULL, &rect);
}
void  GuiOverlay::draw_won_overlay(){

}
void GuiOverlay::draw_pause_screen(){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    SDL_Surface* pause_surface = SDL_LoadBMP("src/pause.bmp");
    if(pause_surface == NULL){
            printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
    }

    SDL_Texture* pause_texture = SDL_CreateTextureFromSurface(renderer, pause_surface);
    SDL_FreeSurface(pause_surface);

    SDL_Rect pause_rect;
    pause_rect.x = (GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size)/2 - 594/2;
    pause_rect.y = (GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size)/2 - 367/2;
    pause_rect.w = 594;
    pause_rect.h = 367;
    SDL_RenderCopy(renderer, pause_texture, NULL, &pause_rect);
    SDL_DestroyTexture(pause_texture);
    pause_texture = nullptr;
}
void GuiOverlay::draw_scoreboard(){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    SDL_Surface *score_surface = SDL_CreateRGBSurface(0, 400,400, 32, 0,0,0,0);
    if (score_surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_FillRect(score_surface, NULL, SDL_MapRGB(score_surface->format, 68, 55, 55));
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    if( score_texture == NULL) {
        SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(score_surface);
    score_surface = nullptr;
    SDL_Rect score_rect;
    score_rect.x = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size - GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.y = 0;
    score_rect.w = GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_DestroyTexture(score_texture);
    score_texture = nullptr;
//
////Draw scoreboard texts
    //GAME LOGO
    textmanager->draw_text(renderer, "SNAKENATOR", 5, 10, 300, 35);

    int score_board_x = (GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size - GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size) + 20;
   //SCOREBOARD TITLE
   //
    textmanager->draw_text(renderer, "Score Board", score_board_x, 10, 180, 25);

    //SCOREBOARD APPLES ATE
    textmanager->draw_text(renderer, textmanager->string_int_concatenation("Apples: ", GameManager::instance()->get_apples_ate()).c_str(), score_board_x, 135, 180, 25);
    //
    //Text  APPLES ATE
    textmanager->draw_text(renderer, textmanager->string_int_concatenation("Score: ", GameManager::instance()->get_game_score()).c_str(), score_board_x, 180, 180, 25);

    //Text Movements Made
    textmanager->draw_text(renderer, textmanager->string_int_concatenation("Steps: ", GameManager::instance()->get_movements_made()).c_str(), score_board_x, 225, 180, 25);


}
GuiOverlay::~GuiOverlay(){
    SDL_DestroyTexture(main_title_bg_texture);
    main_title_bg_texture = nullptr;
    delete(textmanager);
    textmanager = nullptr;
};

