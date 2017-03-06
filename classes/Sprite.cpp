#include "Sprite.h"
//https://github.com/leethomason/tinyxml2
////https://developer.apple.com/library/content/documentation/General/Conceptual/lldb-guide/chapters/C5-Examining-The-Call-Stack.html
Sprite::Sprite(const char* file, SDL_Renderer* renderer){
    std::string const_to_string(file);
    sprite_name = const_to_string;
    const_to_string.append(".json");
    //
    //Parse JSON file to json_doc Document
    FILE* fp = fopen(const_to_string.c_str(), "r");
    char readBuffer[65536];
    rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
    json_doc.ParseStream(is);
    fclose(fp);

    std::string bmp_file(file);
    bmp_file.append(".bmp");
    SDL_Surface* sprite_surface  = SDL_LoadBMP(bmp_file.c_str());
    SDL_SetColorKey(sprite_surface, SDL_TRUE, 0xFF0094);
    sprite_texture = SDL_CreateTextureFromSurface(renderer, sprite_surface);
    SDL_FreeSurface(sprite_surface);
    sprite_renderer = renderer;
};
void Sprite::drawEx(int w, int h, int x , int y, int dest_w, int dest_h, int dest_x, int dest_y, int angle){

};
void Sprite::draw(int w, int h, int x , int y, int dest_w, int dest_h, int dest_x, int dest_y){

};
void Sprite::draw_animated(int w, int h, int dest_x, int dest_y, int dest_w, int dest_h){

};
void Sprite::draw_animated(int dest_x, int dest_y){

    //get current animation frame
    int current_frame = GameManager::instance()->get_animation_frame();

    //get frame node
    const rapidjson::Value& frames = json_doc["frames"][current_frame];

    //get params for draw
    int sprite_width = frames["frame"]["w"].GetInt();
    int sprite_height = frames["frame"]["h"].GetInt();
    int sprite_x = frames["frame"]["x"].GetInt();
    int sprite_y = frames["frame"]["y"].GetInt();

    SDL_Rect apple_rect;
    apple_rect.x = sprite_x;
    apple_rect.y = sprite_y;
    apple_rect.w = sprite_width;
    apple_rect.h = sprite_height;
    SDL_Rect apple_rect_dest;
    apple_rect_dest.x = dest_x*sprite_width;
    apple_rect_dest.y = dest_y*sprite_height;
    apple_rect_dest.w = sprite_width;
    apple_rect_dest.h = sprite_height;
    SDL_RenderCopyEx(sprite_renderer, sprite_texture, &apple_rect, &apple_rect_dest, 0/* angle */, NULL, SDL_FLIP_NONE);

};
Sprite::~Sprite(){
    SDL_DestroyTexture(sprite_texture);
};

