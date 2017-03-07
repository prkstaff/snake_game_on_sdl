#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "Game.h"
#include "Command.h"
#include "GameManager.h"

Command* InputHandler::handle_input(){
            while(SDL_PollEvent( &sdl_event ) != 0){
                if( sdl_event.type == SDL_QUIT ){
                    GameManager::instance()->set_game_is_running(false);
                }else if(sdl_event.type == SDL_KEYDOWN){
                    switch( sdl_event.key.keysym.sym ){
                            case SDLK_UP:
                                return go_up;
                                //*direction = UP;
                            break;
                            case SDLK_DOWN:
                                return go_down;
                                //*direction = DOWN;
                            break;
                            case SDLK_LEFT:
                                return go_left;
                                //*direction = LEFT;
                            break;
                            case SDLK_RIGHT:
                                return go_right;
                                //*direction = RIGHT;
                            break;
                            case SDLK_ESCAPE:
                                GameManager::instance()->set_game_state(PAUSED);
                            break;
                            case SDLK_c:
                                GameManager::instance()->set_game_state(RUNNING);
                            break;
                        }
                }
            }
            return NULL;
};
InputHandler::InputHandler(){
    go_up  = new GoUp();
    go_down  = new GoDown();
    go_right  = new GoRight();
    go_left  = new GoLeft();
};

