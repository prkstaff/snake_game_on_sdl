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
//http://www.lazyfoo.net/SDL_tutorials/lesson11/index.php
//Install sdl2 sdlt_ttf and sdl2_mixer with brew
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
const int  Game::SCREEN_WIDTH = 19;
const int Game::SCREEN_HEIGHT = 12;
const int Game::SCORE_BOARD_WIDTH = 4;
int Game::game_score = 0;
int Game::apples_ate = 0;
int Game::movements_made = 0;
bool Game::game_is_running = true;
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
        SDL_CreateWindowAndRenderer( SCREEN_WIDTH*snake_sprite_square_size, SCREEN_HEIGHT*snake_sprite_square_size, SDL_WINDOW_RESIZABLE, &window, &renderer);
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
           surface = SDL_LoadBMP("/Users/renato/projectspace/snakegame/src/snake_apple_90x90x450.bmp");
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
    Command* command_ = input_handler.handle_input(&game_is_running, sdl_event);
    if(command_){
        command_->execute(&snake);
    }
    snake.move_if_empty(&apple_position);

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
    grass_rect.w = SCREEN_WIDTH*snake_sprite_square_size-SCORE_BOARD_WIDTH*snake_sprite_square_size;
    grass_rect.h = SCREEN_HEIGHT*snake_sprite_square_size;
    SDL_RenderCopy(renderer, grass_texture, NULL, &grass_rect);
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
    score_rect.x = SCREEN_WIDTH*snake_sprite_square_size - SCORE_BOARD_WIDTH*snake_sprite_square_size;
    score_rect.y = 0;
    score_rect.w = SCORE_BOARD_WIDTH*snake_sprite_square_size;
    score_rect.h = SCREEN_HEIGHT*snake_sprite_square_size;
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_DestroyTexture(score_texture);

//Draw scoreboard texts
    TextDraw textmanager;
    //GAME LOGO
    textmanager.draw_text(renderer, "src/kongtext.ttf", "SNAKENATOR", 5, 10, 24, 300, 35);

    //
    int score_board_x = (SCREEN_WIDTH*snake_sprite_square_size - SCORE_BOARD_WIDTH*snake_sprite_square_size) + 20;
    //SCOREBOARD TITLE
    //
    //
    textmanager.draw_text(renderer, "src/kongtext.ttf", "Score Board", score_board_x, 10, 24, 180, 25);

    //SCOREBOARD APPLES ATE
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Apples: ", apples_ate).c_str(), score_board_x, 135, 24, 180, 25);

    //Text  APPLES ATE
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Score: ", game_score).c_str(), score_board_x, 180, 24, 180, 25);

    //Text Movements Made
    textmanager.draw_text(renderer, "src/kongtext.ttf", textmanager.string_int_concatenation("Steps: ", movements_made).c_str(), score_board_x, 225, 24, 180, 25);
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
    if(initSDLScreen()){
        while(game_is_running){
            //processInput();
            updateGame();
            SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0xff, 0xff);
            //SDL_SetRenderDrawColor(renderer, 0x09, 0x51, 0x18, 0xff);
            SDL_RenderClear(renderer);
            drawGame();
            SDL_RenderPresent(renderer);
            unsigned int microseconds = 300000;
            usleep(microseconds);
            //User requests quit
        }
    }
	closeGame();
};
int Game::get_SCREEN_WIDTH(){
    return SCREEN_WIDTH;
};
int Game::get_SCREEN_HEIGHT(){
    return SCREEN_HEIGHT;
};
int Game::get_apples_ate(){
    return apples_ate;
};
void Game::set_apples_ate(int ates ){
    apples_ate = ates;
};
int Game::get_SCORE_BOARD_WIDTH(){
    return SCORE_BOARD_WIDTH;
};
int Game::get_game_score(){
    return game_score;
};
void Game::set_game_score(int score){
    game_score = score;
};
void Game::set_movements_made(int movements){
    movements_made = movements;
};
void Game::set_game_is_running(bool state){
    game_is_running = state;
};
int Game::get_movements_made(){
    return movements_made;
};
bool Game::get_game_is_running(){
    return game_is_running;
};
