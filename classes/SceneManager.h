#ifndef _SCENEMANAGER_
#define _SCENEMANAGER_
#include <iostream>
#include <vector>
#include "Scene.h"
#include <SDL2/SDL.h>
class SceneManager{
    private:
        std::vector<Scene*> scenes;
        SDL_Renderer* renderer;
    public:
        SceneManager(SDL_Renderer*);
        void update();
        void draw();
        Scene* level_one;
        ~SceneManager();
};
#endif /* ifndef _SCENEMANAGER_
#include <iostream>
class SceneManager{

}; */
