#include "Game.h"
#include <iostream>
#include "Position.h"
#include <unistd.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iostream>
//optimize screensurface http://lazyfoo.net/tutorials/SDL/05_optimized_surface_loading_and_soft_stretching/index.php
//Set transparent bpm color key https://gist.github.com/dghost/87274204fc3fe744214c
Game::Game(int sWidth, int sHeight): SCREEN_WIDTH(sWidth), SCREEN_HEIGHT(sHeight), apple_position(2,2,DOWN){
    game_is_running = true;
    //
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

    //initital snake parts
    Position initial_tale(5,6,DOWN);
    Position initial_body2(5,7,DOWN);
    Position initial_head(5,8,DOWN);
    snakePositions.push_back(initial_tale);
    snakePositions.push_back(initial_body2);
    snakePositions.push_back(initial_head);

};
bool Game::initSDLScreen(){
    bool success = true;
    //Init SDL TTF API
    if(TTF_Init()==-1) {
        printf("TTF_Init: %s\n", TTF_GetError());
        exit(2);
    }
    //Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
        SDL_CreateWindowAndRenderer( SCREEN_WIDTH*snake_sprite_square_size, SCREEN_HEIGHT*snake_sprite_square_size, SDL_WINDOW_RESIZABLE, &window, &renderer);
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

void Game::processInput(){
            while(SDL_PollEvent( &sdl_event ) != 0){
                if( sdl_event.type == SDL_QUIT ){
                    game_is_running = false;
                }else if(sdl_event.type == SDL_KEYDOWN){
                    switch( sdl_event.key.keysym.sym ){
                            case SDLK_UP:
                                direction = UP;
                            break;
                            case SDLK_DOWN:
                                direction = DOWN;
                            break;
                            case SDLK_LEFT:
                                direction = LEFT;
                            break;
                            case SDLK_RIGHT:
                                direction = RIGHT;
                            break;
                            default:
                                direction = DEFAULT;
                            break;
                        }
                }
            }
};

bool Game::check_is_snake_position(int x, int y){
    int has_snake_pos = false;
    for(size_t i = 0; i<snakePositions.size(); i++){
        Position pedaco = snakePositions[i];
        if(pedaco.get_x() == x && pedaco.get_y() == y){
            has_snake_pos = true;
            break;
        }
    }
    return has_snake_pos;
}

void Game::if_its_empty_move_snake(int x, int y, int direct){
    bool is_empty = true;
    //check for snake
    for(size_t i = 0; i < snakePositions.size(); i++){
       if(snakePositions[i].get_x() == x && snakePositions[i].get_y() == y){
           is_empty = false;
           break;
       }
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
        }while(check_is_snake_position(new_x,new_y));
        ate_apple = true;
        apples_ate = apples_ate +1;
        apple_position.set_x_y(new_x,new_y);
        game_score = game_score+10;
    }

    if(is_empty){
        Position newPos(x,y, direct);
        snakePositions.push_back(newPos);
        if(ate_apple == false){
            snakePositions.erase(snakePositions.begin());
        }
        ate_apple = false;
        old_direction = direct;
    }
    movements_made = movements_made +1;
    //else game over
}
void Game::updateGame(){
    Position head = snakePositions[snakePositions.size()-1];
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
std::vector <int> Game::get_snake_params_for_drawing(std::vector <Position> pos, size_t index){
    //vector x, y, angle
        std::vector <int> vector_to_return;
        int original_sprite_size = 90;
        int x_to_return;
        int y_to_return = 0;
        int angle_to_return;
        Position pedaco = pos[index];
        //if the tail, the first pedaco
        if(index==0){
            x_to_return = SNAKE_TAIL*original_sprite_size;//sprite cut x
            Position next_pos = pos[index+1];
            if(next_pos.get_x() > pedaco.get_x()) angle_to_return = 0;//RIGHT
            if(next_pos.get_x() < pedaco.get_x()) angle_to_return = 180;//LEFT
            if(next_pos.get_y() < pedaco.get_y()) angle_to_return = 270;//UP
            if(next_pos.get_y() > pedaco.get_y()) angle_to_return = 90;//DOWN
        //if is the head
        }else if(index == pos.size()-1){
            x_to_return = SNAKE_HEAD*original_sprite_size;//sprite cut x
            if(pedaco.get_direction() == DOWN) angle_to_return = 0;
            if(pedaco.get_direction() == UP) angle_to_return = 180;
            if(pedaco.get_direction() == LEFT) angle_to_return = 90;
            if(pedaco.get_direction() == RIGHT) angle_to_return = 270;
        }else{
            Position previous_pos = pos[index-1];
            Position next_pos = pos[index+1];
            //
            //IF IT IS A TURN
            if(previous_pos.get_x() != next_pos.get_x() && previous_pos.get_y() != next_pos.get_y()){
                x_to_return = SNAKE_BODY_TURN*original_sprite_size;
                if(pedaco.get_direction() == DOWN){
                    // DOWN from left to right
                    if(previous_pos.get_x() < next_pos.get_x()){
                        angle_to_return = 270;
                    }else{
                        angle_to_return = 180;
                    }
                }else if(pedaco.get_direction() == UP){
                    //if its going to the left
                    if(previous_pos.get_x() > next_pos.get_x()){
                        angle_to_return = 90;
                    }else{
                        angle_to_return = 0;
                    }
                }else if(pedaco.get_direction() == RIGHT){
                    //IF is going up
                    if(previous_pos.get_y() > next_pos.get_y()){
                        angle_to_return = 180;
                    }else{
                        angle_to_return = 90;
                    }
                }else if(pedaco.get_direction() == LEFT){
                    //IF is going up
                    if(previous_pos.get_y() > next_pos.get_y()){
                            angle_to_return = 270;
                    }else{
                        angle_to_return = 0;
                    }
                }
            //IF ITS A BODY
            }else{
                x_to_return = SNAKE_BODY*original_sprite_size;//sprite cut x
                if(pedaco.get_direction() == RIGHT || pedaco.get_direction() == LEFT){
                    angle_to_return = 90;
                }else{
                    angle_to_return = 0;
                }
            }
        }

        //fill the vector
        vector_to_return.push_back(x_to_return);
        vector_to_return.push_back(y_to_return);
        vector_to_return.push_back(angle_to_return);

        return vector_to_return;
}
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
// Draw Snake
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
    TTF_Font* Sans = TTF_OpenFont("/Users/renato/projectspace/snakegame/src/kongtext.ttf", 24);
    if(Sans == NULL){
        printf("TTF_OpenFont: %s\n", TTF_GetError());
    }

    SDL_Color White = {255, 255, 255, 0};

    //GAME LOGO
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "SNAKENATOR", White);

    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = 5;
    Message_rect.y = 10;
    Message_rect.w = 300;
    Message_rect.h = 35;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);

    //
    int score_board_x = (SCREEN_WIDTH*snake_sprite_square_size - score_board_width*snake_sprite_square_size) + 20;
    //SCOREBOARD TITLE
    //
    //
    SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, "Score Board", White);

    SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
    SDL_Rect Message_rect2;
    Message_rect2.x = score_board_x;
    Message_rect2.y = 10;
    Message_rect2.w = 180;
    Message_rect2.h = 25;
    SDL_RenderCopy(renderer, Message2, NULL, &Message_rect2);
    SDL_DestroyTexture(Message2);

    //SCOREBOARD APPLES ATE
    std::string apple_text = "Apples: ";
    std::stringstream apples_text_stream;
    apples_text_stream << apple_text << apples_ate;
    SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Sans, apples_text_stream.str().c_str(), White);

    SDL_Texture* Message3 = SDL_CreateTextureFromSurface(renderer, surfaceMessage3);
    SDL_Rect Message_rect3;
    Message_rect3.x = score_board_x;
    Message_rect3.y = 135;
    Message_rect3.w = 180;
    Message_rect3.h = 25;
    SDL_RenderCopy(renderer, Message3, NULL, &Message_rect3);
    SDL_DestroyTexture(Message3);

    //SCOREBOARD APPLES ATE
    std::string score_text = "Score: ";
    std::stringstream score_text_stream;
    score_text_stream << score_text << game_score;
    SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Sans, score_text_stream.str().c_str(), White);

    SDL_Texture* Message4 = SDL_CreateTextureFromSurface(renderer, surfaceMessage4);
    SDL_Rect Message_rect4;
    Message_rect4.x = score_board_x;
    Message_rect4.y = 180;
    Message_rect4.w = 180;
    Message_rect4.h = 25;
    SDL_RenderCopy(renderer, Message4, NULL, &Message_rect4);
    SDL_DestroyTexture(Message4);

    //SCOREBOARD APPLES ATE
    std::string step_text = "Steps: ";
    std::stringstream step_text_stream;
    step_text_stream << step_text << movements_made;
    SDL_Surface* surfaceMessage5 = TTF_RenderText_Solid(Sans, step_text_stream.str().c_str(), White);

    SDL_Texture* Message5 = SDL_CreateTextureFromSurface(renderer, surfaceMessage5);
    SDL_Rect Message_rect5;
    Message_rect5.x = score_board_x;
    Message_rect5.y = 225;
    Message_rect5.w = 180;
    Message_rect5.h = 25;
    SDL_RenderCopy(renderer, Message5, NULL, &Message_rect5);
    SDL_DestroyTexture(Message5);

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

