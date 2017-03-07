#ifndef _SCENE__
#define _SCENE__
#include <SDL2/SDL.h>
class Scene{
    protected:
        SDL_Renderer* renderer;
    public:
        virtual void draw() = 0;
        virtual ~Scene();
};
class MainTitleScene: public Scene{
    private:
        SDL_Texture* main_title_bg_texture = 0;
    public:
        virtual void draw();
        MainTitleScene(SDL_Renderer*);
        ~MainTitleScene();
};
class Level1Scene: public Scene{
    private:
        SDL_Texture* grass_texture;
    public:
        virtual void draw();
        Level1Scene(SDL_Renderer*);
        ~Level1Scene();
};


#endif
/* ifndef _SCENE__
class Scene{
    public:
        Scene();
}; */
