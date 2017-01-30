#include "Game.h"

Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight){
    window = NULL;
    screenSurface = NULL;
    game_is_running = true;
};
bool Game::initSDLScreen(){
    bool success = false;
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );
            SDL_UpdateWindowSurface( window );
            SDL_Delay(10000);
		}
	}

	return success;

}
void Game::processInput(){

};
void Game::updateGame(){

};
void Game::drawGame(){

};
void Game::closeGame(){
    SDL_DestroyWindow( window );
	//Quit SDL subsystems
	SDL_Quit();
}
void Game::run(){
    //This is the game loop
    if(initSDLScreen()){

        while(game_is_running){
            processInput();
            updateGame();
            drawGame();
        }
    }
	closeGame();
};

