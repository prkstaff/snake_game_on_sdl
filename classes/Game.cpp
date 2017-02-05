#include "Game.h"
#include <iostream>
#include "Position.h"
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight){
    game_is_running = true;
    //
    //initial snake position
    snake_sprite_square_size = 60;
    Position initial_tale(5,5,DOWN);
    Position initial_body1(5,6,DOWN);
    Position initial_body2(5,7,DOWN);
    Position initial_head(5,8,DOWN);
    snakePositions.push_back(initial_tale);
    snakePositions.push_back(initial_body1);
    snakePositions.push_back(initial_body2);
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
std::vector <int> Game::get_snake_params_for_drawing(std::vector <Position> pos, size_t index){
    //vector x, y, angle
        std::vector <int> vector_to_return;
        int x_to_return;
        int y_to_return = 0;
        int angle_to_return;
        Position pedaco = pos[index];
        //if the tail, the first pedaco
        if(index==0){
            x_to_return = SNAKE_TAIL*90;//sprite cut x
            if(pedaco.get_direction() == DOWN) angle_to_return = 90;
            if(pedaco.get_direction() == UP) angle_to_return = 270;
            if(pedaco.get_direction() == LEFT) angle_to_return = 180;
            if(pedaco.get_direction() == RIGHT) angle_to_return = 0;
        //if is the head
        }else if(index == pos.size()-1){
            x_to_return = SNAKE_HEAD*90;//sprite cut x
            if(pedaco.get_direction() == DOWN) angle_to_return = 0;
            if(pedaco.get_direction() == UP) angle_to_return = 180;
            if(pedaco.get_direction() == LEFT) angle_to_return = 90;
            if(pedaco.get_direction() == RIGHT) angle_to_return = 270;
        }else{
            x_to_return = SNAKE_BODY*90;//sprite cut x
            angle_to_return = 0;
        }

        //fill the vector
        vector_to_return.push_back(x_to_return);
        vector_to_return.push_back(y_to_return);
        vector_to_return.push_back(angle_to_return);

        return vector_to_return;
}
void Game::drawGame(){
    for(size_t i = 0; i < snakePositions.size(); i++){
        Position pedaco = snakePositions[i];
        SDL_Rect src;
        std::vector <int> my_vect = get_snake_params_for_drawing(snakePositions,i);
        src.x = my_vect[0];
        src.y = my_vect[1];
        src.w = 90;
        src.h = 90;
        SDL_Rect dest;
        dest.x = pedaco.get_x()*snake_sprite_square_size;
        dest.y = pedaco.get_y()*snake_sprite_square_size;
        dest.w = snake_sprite_square_size;//tamanho o tile da cobra para exibir
        dest.h = snake_sprite_square_size;//tamanho o tile da cobra para exibir
        SDL_RenderCopyEx(renderer, sprites, &src, &dest, my_vect[2]/* angle */, NULL, SDL_FLIP_NONE);
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

