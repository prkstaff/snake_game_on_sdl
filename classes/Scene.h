#ifndef _SCENE__
#define _SCENE__
#include <SDL2/SDL.h>
  class Scene{
    private:
    public:
        virtual void draw(SDL_Renderer*) = 0;
        virtual ~Scene();
};
class MainTitleScene: public Scene{
    public:
        void draw(SDL_Renderer* renderer);
        ~MainTitleScene();
};

#endif
/* ifndef _SCENE__
class Scene{
    public:
        Scene();
}; */
