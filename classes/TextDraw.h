#ifndef _TEXTDRAW_
#include <iostream>
#include <string>
#include <sstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>
class TextDraw{
    private:
        TTF_Font* Sans;
        SDL_Color color;
    public:
        void draw_text(SDL_Renderer *renderer, const char *font_string, int x_pos, int y_pos, int rect_w, int rect_h);
        TextDraw(const char*, int);
        ~TextDraw();
        std::string string_int_concatenation(std::string the_string, int the_int);
};
#define _TEXTDRAW_
#endif /* ifndef _TEXTDRAW_ */
