#ifndef _TEXTDRAW_
#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
class TextDraw{
    private:
    public:
        void draw_text(SDL_Renderer *renderer, const char *font, const char *font_string, int size, int x_pos, int y_pos, int rect_w, int rect_h);
        TextDraw();
        std::string string_int_concatenation(std::string the_string, int the_int);
};
#define _TEXTDRAW_
#endif /* ifndef _TEXTDRAW_ */
