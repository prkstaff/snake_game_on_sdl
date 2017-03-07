#include "SceneManager.h"

SceneManager::SceneManager(SDL_Renderer* therenderer){
    renderer = therenderer;
    level_one = new Level1Scene(renderer);
    scenes.push_back(level_one);
}
void SceneManager::draw(){
    scenes[0]->draw();
}
SceneManager::~SceneManager(){
 //   for (unsigned int i; i < scenes.size(); ++i){
 //     delete (scenes[i]);
 //   };
 //   scenes.clear();
}
