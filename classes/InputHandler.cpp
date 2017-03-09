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
                }else if(sdl_event.type == SDL_CONTROLLERBUTTONDOWN){
                    //https://forums.libsdl.org/viewtopic.php?p=47268&sid=5e3d5a828c7b937e9d9fd9218add3f4b
                    switch(sdl_event.cbutton.button)
                    {
                         case SDL_CONTROLLER_BUTTON_Y:
                             return go_up;
                         break;
                         case SDL_CONTROLLER_BUTTON_X:
                            return go_left;
                         break;
                         case SDL_CONTROLLER_BUTTON_B:
                             return go_right;
                         break;
                         case SDL_CONTROLLER_BUTTON_A:
                             return go_down;
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

