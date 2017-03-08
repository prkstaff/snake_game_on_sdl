#include "Game.h"
#include <iostream>
#include "Position.h"
#include <unistd.h>
#include <SDL2/SDL_mixer.h>
#include <string>
#include <sstream>
#include <iostream>
#include "Sound.h"
#include "Command.h"
#include "GuiOverlay.h"
#include <SDL2/SDL_ttf.h>
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
        GuiOverlay gui_overlay(renderer);
        while(GameManager::instance()->get_game_is_running()){
            scene_manager->update();
            SDL_RenderClear(renderer);
            //DRAW
                if(GameManager::instance()->get_game_state() == RUNNING || GameManager::instance()->get_game_state() == PAUSED){
                    scene_manager->draw();
                }
                // Handles game state and draw main_title, pause, scoreboard and etc.
                gui_overlay.draw();

                SDL_RenderPresent(renderer);
                SDL_Delay(GameManager::instance()->get_ms_per_frame()*10);
                GameManager::instance()->update_animation_frame();
        }
    }
	closeGame();
};

