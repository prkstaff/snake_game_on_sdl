#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include <SDL2/SDL.h>
#include <iostream>
#include "Command.h"

class InputHandler{
    public:
        Command* handle_input(bool *game_is_running, SDL_Event sdl_event);
        InputHandler();
    private:
        Command* go_up;
        Command* go_down;
        Command* go_left;
        Command* go_right;
        Command* pause;
};
#endif /* ifndef _INPUTHANDLER_
class InputHandler{
    public:
        void handle_input();
    private:
        //handle commands

} */
