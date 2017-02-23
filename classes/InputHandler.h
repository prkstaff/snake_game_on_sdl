#ifndef _INPUTHANDLER_
#define _INPUTHANDLER_

#include <SDL2/SDL.h>
#include <iostream>

class InputHandler{
    public:
        void handle_input(bool *game_is_running, SDL_Event sdl_event, int* direction);
    private:
        //handle commands
};
#endif /* ifndef _INPUTHANDLER_
class InputHandler{
    public:
        void handle_input();
    private:
        //handle commands

} */
