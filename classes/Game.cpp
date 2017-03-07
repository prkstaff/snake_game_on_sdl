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
Game::Game(){
};
bool Game::initSDLScreen(){
    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
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
	}
	return success;

}
void Game::drawGame(){

    int snake_sprite_square_size = GameManager::instance()->get_snake_sprite_square_size();
    // TODO, create ScoreBoard class with draw mathod and refactor below
    //
//Draw Score Board
    //score_board.draw_score_board(render);
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
    SDL_Rect score_rect;
    score_rect.x = GameManager::instance()->get_SCREEN_WIDTH()*snake_sprite_square_size - GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.y = 0;
    score_rect.w = GameManager::instance()->get_SCORE_BOARD_WIDTH()*snake_sprite_square_size;
    score_rect.h = GameManager::instance()->get_SCREEN_HEIGHT()*snake_sprite_square_size;
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_DestroyTexture(score_texture);
    score_texture = nullptr;

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
    };
    SDL_RenderPresent(renderer);
};
void Game::closeGame(){
    delete(level_one);
    delete(scene_manager);
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
        scene_manager = new SceneManager(renderer);
        MainTitleScene main_title_scene(renderer);
        while(GameManager::instance()->get_game_is_running()){
            scene_manager->update();
            SDL_RenderClear(renderer);
            //DRAW
                if(GameManager::instance()->get_game_state() == RUNNING || GameManager::instance()->get_game_state() == PAUSED){
                    scene_manager->draw();
                    //drawGame();
                }
                if(GameManager::instance()->get_game_state() == MAIN_SCREEN)main_title_scene.draw_bg();
                SDL_RenderPresent(renderer);
                SDL_Delay(GameManager::instance()->get_ms_per_frame()*10);
                GameManager::instance()->update_animation_frame();
        }
    }
	closeGame();
};

