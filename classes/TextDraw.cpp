#include "TextDraw.h"

TextDraw::TextDraw(const char *font, int size){
    Sans = TTF_OpenFont(font, size);
    color = {255, 255, 255, 0};
}
void TextDraw::draw_text(SDL_Renderer *renderer,  const char *font_string, int x_pos, int y_pos, int rect_w, int rect_h){
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, font_string, color);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_FreeSurface(surfaceMessage);
    surfaceMessage = nullptr;

    SDL_Rect Message_rect;
    Message_rect.x = x_pos;
    Message_rect.y = y_pos;
    Message_rect.w = rect_w;
    Message_rect.h = rect_h;
    SDL_RenderCopy(renderer, Message, NULL, &Message_rect);
    //http://stackoverflow.com/questions/19719762/are-there-any-alternatives-to-valgrind-on-mac-os-x-mountain-lion-and-mavericks-t
    SDL_DestroyTexture(Message);
    Message = nullptr;
};
std::string TextDraw::string_int_concatenation(std::string the_string, int the_int){
    std::string my_str;
    my_str = the_string + std::to_string(the_int);
    return my_str;
};
TextDraw::~TextDraw(){

}
