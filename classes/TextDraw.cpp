#include "TextDraw.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <sstream>
#include <iostream>

TextDraw::TextDraw(){

}
void TextDraw::draw_text(SDL_Renderer *renderer, const char *font, const char *font_string, int x_pos, int y_pos, int size, int rect_w, int rect_h){
    TTF_Font* Sans = TTF_OpenFont(font, size);
    SDL_Color White = {255, 255, 255, 0};
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, font_string, White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect;
    Message_rect.x = x_pos;
    Message_rect.y = y_pos;
    Message_rect.w = rect_w;
    Message_rect.h = rect_h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    SDL_DestroyTexture(Message);
};

std::string TextDraw::string_int_concatenation(std::string the_string, int the_int){
    std::string my_str;
    my_str = the_string + std::to_string(the_int);
    return my_str;
};
