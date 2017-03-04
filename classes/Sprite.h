#ifndef __SPRITE__
#define __SPRITE__

#include <iostream>
#include <SDL2/SDL.h>
#include "GameManager.h"
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"
#include <cstdio>

class Sprite{
    private:
        Uint32 ColorKey;
        SDL_Texture* sprite_texture;
        SDL_Renderer* sprite_renderer;
        std::string sprite_name;
        rapidjson::Document json_doc;
    public:
        ~Sprite();
        Sprite(const char* file, SDL_Renderer* renderer);
        void drawEx(int w, int h, int x , int y, int dest_w, int dest_h, int dest_x, int dest_y, int angle);
        void draw(int w, int h, int x , int y, int dest_w, int dest_h, int dest_x, int dest_y);
        void draw_animated(int w, int h, int dest_x, int dest_y, int dest_w, int dest_h);
        void draw_animated(int dest_x, int dest_y);
};
#endif
/* ifndef __SPRITE__

#include <iostream>

class Sprite{
    private:
        int x;
        int y;
        int w;
        int h;
        std::string image_path;
    public:
        virtual Sprite(int x, int y, int w, int h)

};
class SpriteFromBmp{

};
class SpriteFromJpeg{

};
class SpriteFromPng{

}; */
