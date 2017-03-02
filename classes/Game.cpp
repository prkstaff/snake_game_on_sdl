#include "Game.h"
#include <iostream>
#include "Position.h"
#include "TextDraw.h"
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Sound.h"
#include "Command.h"
//#include "Scene.cpp"
//http://www.lazyfoo.net/SDL_tutorials/lesson11/index.php
//Install sdl2 sdlt_ttf and sdl2_mixer with brew
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
Game::Game():apple_position(2,2,DOWN), snake(5,2){
    //initial snake position
    //
    Position apple_position(2,2, DOWN);
    snake_sprite_square_size = 60;
    //
    //Score board width
    Snake snake(5,2);
    //initialize snake
};
bool Game::initSDLScreen(){
    bool success = true;
    //Init SDL TTF API
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        SDL_CreateWindowAndRenderer( GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size, GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size, SDL_WINDOW_RESIZABLE, &window, &renderer);
                         //Initialize SDL_mixer
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
        {
            printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
            success = false;
        }
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
           surface = SDL_LoadBMP("src/snake_apple_90x90x450.bmp");
           SDL_SetColorKey(surface, SDL_TRUE, 0xFFFFFF);
            if(surface == NULL){
                printf( "BMP could not Loaded! SDL_Error: %s\n", SDL_GetError() );
            }else{
                sprites = SDL_CreateTextureFromSurface(renderer, surface);
                if(sprites == NULL){
                    printf( "sprite could not be created! SDL_Error: %s\n", SDL_GetError() );
                }else{
                    SDL_FreeSurface(surface);
                    //Create window
                }
            }
        }
	}
	return success;

}
void Game::updateGame(){
    Command* command_ = input_handler.handle_input(sdl_event);
    if(command_){
        command_->execute(&snake);
    }
    if(GameManager::instance()->get_game_state() == RUNNING){
        snake.move_if_empty(&apple_position);
    }

};
void Game::draw_main_screen(){
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
};
void Game::drawGame(){

// Draw the grass
    SDL_Surface *grass_surface = SDL_LoadBMP("src/grass.bmp");
    SDL_Texture *grass_texture = SDL_CreateTextureFromSurface(renderer, grass_surface);
    if (grass_texture == NULL) {
        fprintf(stderr, "CreateTextureFromSurface failed: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_FreeSurface(grass_surface);
    grass_surface = NULL;
    SDL_Rect grass_rect;
    grass_rect.x = 0;
    grass_rect.y = 0;
    grass_rect.w = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size-GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    grass_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, grass_texture, NULL, &grass_rect);
    SDL_DestroyTexture(grass_texture);
    //
    // Todo, create apple class with a draw method and refactor below
    //
// Draw Apple
    SDL_Rect apple_rect;
    apple_rect.x = 4*90;
    apple_rect.y = 0;
    apple_rect.w = 90;
    apple_rect.h = 90;
    SDL_Rect apple_rect_dest;
    apple_rect_dest.x = apple_position.get_x()*snake_sprite_square_size;
    apple_rect_dest.y = apple_position.get_y()*snake_sprite_square_size;
    apple_rect_dest.w = snake_sprite_square_size;
    apple_rect_dest.h = snake_sprite_square_size;
    SDL_RenderCopyEx(renderer, sprites, &apple_rect, &apple_rect_dest, 0/* angle */, NULL, SDL_FLIP_NONE);
    //
    // TODO, create draw method in snake class and refactor below
    //
// Draw Snake
    snake.draw(renderer, snake_sprite_square_size, sprites);
    // TODO, create ScoreBoard class with draw mathod and refactor below
    //
//Draw Score Board
    //score_board.draw_score_board(render);
    SDL_Surface *score_surface = SDL_CreateRGBSurface(0, 400,400, 32, 0,0,0,0);
    if (surface == NULL) {
        SDL_Log("SDL_CreateRGBSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_FillRect(score_surface, NULL, SDL_MapRGB(score_surface->format, 68, 55, 55));
    SDL_Texture *score_texture = SDL_CreateTextureFromSurface(renderer, score_surface);
    if( score_texture == NULL) {
        SDL_Log("SDL_CreateTextureFromSurface() failed: %s", SDL_GetError());
        exit(1);
    }
    SDL_Rect score_rect;
    score_rect.x = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size - GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.y = 0;
    score_rect.w = GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_DestroyTexture(score_texture);

//Draw scoreboard texts
    TextDraw textmanager;
    //GAME LOGO
    textmanager.draw_text(renderer, "src/kongtext.ttf", "SNAKENATOR", 5, 10, 24, 300, 35);

    //
    int score_board_x = (GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size - GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size) + 20;
    //SCOREBOARD TITLE
    //
    //
    textmanager.draw_text(renderer, "src/kongtext.ttf", "Score Board", score_board_x, 10, 24, 180, 25);

    //SCOREBOARD APPLES ATE
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Apples: ", GameManager::instance()->get_apples_ate()).c_str(), score_board_x, 135, 24, 180, 25);
    //
    //Text  APPLES ATE
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Score: ", GameManager::instance()->get_game_score()).c_str(), score_board_x, 180, 24, 180, 25);

    //Text Movements Made
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Steps: ", GameManager::instance()->get_movements_made()).c_str(), score_board_x, 225, 24, 180, 25);

    if(GameManager::instance()->get_game_state() == PAUSED){
        SDL_Surface* pause_surface = SDL_LoadBMP("src/pause.bmp");
        SDL_Texture* pause_texture = SDL_CreateTextureFromSurface(renderer, pause_surface);
        SDL_FreeSurface(pause_surface);

        SDL_Rect pause_rect;
        pause_rect.x = (GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size)/2 - 594/2;
        pause_rect.y = (GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size)/2 - 367/2;
        pause_rect.w = 594;
        pause_rect.h = 367;
        SDL_RenderCopy(renderer, pause_texture, NULL, &pause_rect);
        SDL_DestroyTexture(pause_texture);
    };
    SDL_RenderPresent(renderer);
};
void Game::closeGame(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    window = NULL;
	//Quit SDL subsystems
    printf("Quitting!! \n");
	SDL_Quit();
}
void Game::run(){
    //This is the game loop
    //Scene* main_title_scene = new MainTitleScene();
    if(initSDLScreen()){
        while(GameManager::instance()->get_game_is_running()){
            updateGame();
            //DRAW
                if(GameManager::instance()->get_game_state() == RUNNING || GameManager::instance()->get_game_state() == PAUSED)drawGame();
                if(GameManager::instance()->get_game_state() == MAIN_SCREEN)draw_main_screen();
            SDL_Delay(GameManager::instance()->get_ms_per_frame());
            //User requests quit
        }
    }
	closeGame();
};

