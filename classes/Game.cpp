#include "Game.h"
#include <iostream>
#include "Position.h"
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight){
    game_is_running = true;
    Position initial_head(5,5,DOWN);
    Position initial_tale(5,6,DOWN);
    snakePositions.push_back(initial_tale);
    snakePositions.push_back(initial_head);

    //initital snake parts
};
bool Game::initSDLScreen(){
    bool success = true;
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        SDL_CreateWindowAndRenderer( SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE, &window, &renderer);
        if( window == NULL )
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Get window surface
           SDL_SetWindowPosition(window, 65, 126);
           surface = SDL_LoadBMP("/Users/renato/projectspace/snakegame/src/snake_apple_90x90x450.bmp");
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

void Game::processInput(){
            while(SDL_PollEvent( &sdl_event ) != 0){
                if( sdl_event.type == SDL_QUIT ){
                    game_is_running = false;
                }else if(sdl_event.type == SDL_KEYDOWN){
                    switch( sdl_event.key.keysym.sym ){
                            case SDLK_UP:
                                direction = UP;
                                printf("UP \n");
                            break;
                            case SDLK_DOWN:
                                direction = DOWN;
                                printf("down \n");
                            break;
                            case SDLK_LEFT:
                                direction = LEFT;
                                printf("left \n");
                            break;
                            case SDLK_RIGHT:
                                direction = RIGHT;
                                printf("right \n");
                            break;
                            default:
                                printf("default \n");
                            break;
                        }
                }
            }
};
void Game::updateGame(){

};
void Game::drawGame(){
    for(size_t i = 0; i < snakePositions.size(); i++){
        Position pedaco = snakePositions[i];
        SDL_Rect src;
        src.x = 0;//sprite cut x
        src.y = 0;
        src.w = 90;
        src.h = 90;
        SDL_Rect dest;
        dest.x = pedaco.get_x()*60;
        dest.y = pedaco.get_y()*60;
        dest.w = 60;//tamanho o tile da cobra para exibir
        dest.h = 60;//tamanho o tile da cobra para exibir
        SDL_RenderCopyEx(renderer, sprites, &src, &dest, 0, NULL, SDL_FLIP_NONE);
    }
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
            processInput();
            updateGame();
            SDL_SetRenderDrawColor(renderer, 0x09, 0x51, 0x18, 0xff);
            SDL_RenderClear(renderer);
            drawGame();
            SDL_RenderPresent(renderer);
            //User requests quit
        }
    }
	closeGame();
};

