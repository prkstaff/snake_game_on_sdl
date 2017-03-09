#ifndef __GAMEOVERLAY_
#define __GAMEOVERLAY_
#include <SDL2/SDL.h>
#include "GameManager.h"
#include "TextDraw.h"

//Handles Screen Scores, Pauses, things that overlay all game Lelels
class GuiOverlay{
    private:
        //Main Title Vars
        SDL_Texture* main_title_bg_texture = 0;
        //General
        SDL_Renderer* renderer;
        TextDraw* textmanager;
    public:
        void draw_main_title();
        void draw_won_overlay();
        void draw_pause_screen();
        void draw_scoreboard();
        void draw();
        GuiOverlay(SDL_Renderer*);
        ~GuiOverlay();
};
#endif /* ifndef meOver */
