#include "InputHandler.h"
#include <SDL2/SDL.h>
#include "Game.h"

void InputHandler::handle_input(bool *game_is_running, SDL_Event sdl_event, int* direction){
            while(SDL_PollEvent( &sdl_event ) != 0){
                if( sdl_event.type == SDL_QUIT ){
                    *game_is_running = false;
                }else if(sdl_event.type == SDL_KEYDOWN){
                    switch( sdl_event.key.keysym.sym ){
                            case SDLK_UP:
                                *direction = UP;
                            break;
                            case SDLK_DOWN:
                                *direction = DOWN;
                            break;
                            case SDLK_LEFT:
                                *direction = LEFT;
                            break;
                            case SDLK_RIGHT:
                                *direction = RIGHT;
                            break;
                            default:
                                *direction = DEFAULT;
                            break;
                        }
                }
            }

};
