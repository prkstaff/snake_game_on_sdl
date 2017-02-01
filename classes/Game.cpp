#include "Game.h"

Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight){
    window = NULL;
    screenSurface = NULL;
    game_is_running = true;
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
		}
	}
	return success;

}
void Game::placeExitButton(){
    closeButton = SDL_LoadBMP("src/closebuttonbmp.bmp");
    if(closeButton == NULL){
        printf("Unable to load exit button %s! SDL ERROR: %s\n", "/Users/renato/projectspace/snakegame/src/closebuttonbmp.bmp", SDL_GetError() );
    }
    SDL_BlitSurface(closeButton, NULL, screenSurface, NULL );
    SDL_UpdateWindowSurface(window);
}
void Game::processInput(){
            while(SDL_PollEvent( &sdl_event ) != 0){
                if( sdl_event.type == SDL_QUIT ){
                    game_is_running = false;
                }
            }
};
void Game::updateGame(){

};
void Game::drawGame(){

};
void Game::closeGame(){
    SDL_FreeSurface(closeButton);
    closeButton = NULL;

    SDL_DestroyWindow( window );
    window = NULL;
	//Quit SDL subsystems
    printf("Quitting!! \n");
	SDL_Quit();
}
void Game::run(){
    //This is the game loop
    if(initSDLScreen()){
        placeExitButton();
        while(game_is_running){
            processInput();
            updateGame();
            drawGame();
            //User requests quit
        }
    }
	closeGame();
};

