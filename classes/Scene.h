#ifndef _SCENE__
#define _SCENE__
#include <SDL2/SDL.h>
#include "Sprite.h"
#include "Snake.h"
#include "Position.h"
#include "InputHandler.h"
#include "Command.h"

class Scene{
    protected:
        SDL_Renderer* renderer;
    public:
        virtual void draw_bg() = 0;
        virtual void draw_objects() = 0;
        virtual void draw_snake() = 0;
        virtual void update() = 0;
        virtual ~Scene();
};
class MainTitleScene: public Scene{
    private:
        SDL_Texture* main_title_bg_texture = 0;
    public:
        virtual void draw_bg();
        virtual void draw_objects();
        virtual void draw_snake();
        virtual void update();
        MainTitleScene(SDL_Renderer*);
        ~MainTitleScene();
};
class Level1Scene: public Scene{
    private:
        SDL_Texture* grass_texture;
        Position* apple_position;
        Command* command;
        Sprite* sApple;
        SDL_Texture* snake_sprites;
        SDL_Event sdl_event;
        Snake* snake;
        InputHandler input_handler;
    public:
        virtual void draw_bg();
        virtual void draw_objects();
        virtual void draw_snake();
        virtual void update();

        Level1Scene(SDL_Renderer*);
        ~Level1Scene();
};


#endif
/* ifndef _SCENE__
class Scene{
    public:
        Scene();
}; */
