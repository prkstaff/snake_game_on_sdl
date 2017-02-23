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
//http://www.lazyfoo.net/SDL_tutorials/lesson11/index.php
//Install sdl2 sdlt_ttf and sdl2_mixer with brew
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight), apple_position(2,2,DOWN), snake(5,2){
    game_is_running = true;
    //initial values
    movements_made = 0;
    apples_ate = 0;
    game_score = 0;
    //
    //initial snake position
    Position apple_position(2,2, DOWN);
    ate_apple =  false;
    snake_sprite_square_size = 60;
    //
    //Score board width
    score_board_width = 4;
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


void Game::if_its_empty_move_snake(int x, int y, int direct){
    bool is_empty = true;

    //check for snake
       if(snake.is_snake_position(x, y)){
           is_empty = false;
       }

    //check for map borders
    if(x < 0 || y < 0 || x > SCREEN_WIDTH-score_board_width-1 || y > SCREEN_HEIGHT -1){
        is_empty = false;
    }

    //check if is biting the apple
    if(x == apple_position.get_x() && y == apple_position.get_y()){
        int new_x;
        int new_y;
        do{
            new_x = rand() % (SCREEN_WIDTH - score_board_width) ;
            new_y = rand() % SCREEN_HEIGHT ;
        }while(snake.is_snake_position(new_x,new_y));
        ate_apple = true;
        apples_ate = apples_ate +1;
        //play chomp sound
        Sound::instance()->play_chomp_sound();
        apple_position.set_x_y(new_x,new_y);
        game_score = game_score+10;
    }

    if(is_empty){
        Position newPos(x,y, direct);
        snake.add_position(newPos);
        if(ate_apple == false){
            snake.erase_first_position();
        }
        ate_apple = false;
        old_direction = direct;
        movements_made = movements_made +1;
    }
    //else game over
}
void Game::updateGame(){
    Position head = snake.get_positions()[snake.get_positions().size()-1];
    //
    //dont let snake go backwards
    if((direction==RIGHT && old_direction==LEFT) || (direction==LEFT && old_direction==RIGHT))direction = old_direction;
    if((direction==DOWN && old_direction==UP) || (direction==UP && old_direction==DOWN))direction = old_direction;

    if(direction != DEFAULT){
        if(direction == RIGHT){
                if_its_empty_move_snake(head.get_x()+1,head.get_y(), RIGHT);
        }else if(direction == LEFT){
                if_its_empty_move_snake(head.get_x()-1,head.get_y(), LEFT);
        }else if(direction == UP){
                if_its_empty_move_snake(head.get_x(),head.get_y()-1, UP);
        }else if(direction == DOWN){
                if_its_empty_move_snake(head.get_x(),head.get_y()+1, DOWN);
        }
    }
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
    grass_rect.w = SCREEN_WIDTH*snake_sprite_square_size-score_board_width*snake_sprite_square_size;
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
    score_rect.x = SCREEN_WIDTH*snake_sprite_square_size - score_board_width*snake_sprite_square_size;
    score_rect.y = 0;
    score_rect.w = score_board_width*snake_sprite_square_size;
    score_rect.h = SCREEN_HEIGHT*snake_sprite_square_size;
    SDL_RenderCopy(renderer, score_texture, NULL, &score_rect);
    SDL_DestroyTexture(score_texture);

//Draw scoreboard texts
    TextDraw textmanager;
    //GAME LOGO
    textmanager.draw_text(renderer, "src/kongtext.ttf", "SNAKENATOR", 5, 10, 24, 300, 35);

    //
    int score_board_x = (SCREEN_WIDTH*snake_sprite_square_size - score_board_width*snake_sprite_square_size) + 20;
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
            input_handler.handle_input(&game_is_running, sdl_event, &direction);
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

