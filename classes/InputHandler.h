#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include <SDL2/SDL.h>
#include <iostream>
#include "Command.h"

class InputHandler{
    public:
        Command* handle_input();
        InputHandler();
    private:
        SDL_Event sdl_event;
        Command* go_up;
        Command* go_down;
        Command* go_left;
        Command* go_right;
};
#endif /* ifndef _INPUTHANDLER_
class InputHandler{
    public:
        void handle_input();
    private:
        //handle commands

} */
