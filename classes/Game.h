#ifndef GAME_H
#define GAME_H

#include <SDL2/SDL.h>
#include <stdio.h>
#include <string>
#include "Position.h"
#include "InputHandler.h"
#include <vector>
#include "Snake.h"
#include "GameManager.h"
#include "Scene.h"
#include "Sprite.h"
#include "SceneManager.h"

//26m https://www.youtube.com/watch?v=nK_sT12h22s&list=PLt1n3PgXIOdmpmI_0PTOad7W0MlyAbHod&index=2
//
class Game
{
    private:
		SDL_Joystick *joy;
        SDL_Surface *surface;
        Scene* level_one = 0;
        SDL_Texture *sprite;
        SDL_Window *window;
        SDL_Renderer *renderer;
        SDL_Texture *sprites;
        SceneManager* scene_manager;
        //SDL_Surface* loadSurface( std::string path);
        bool check_is_snake_position(int x, int y);
        bool initSDLScreen();
        void processInput();
        void draw_main_screen();
        void closeGame();
    public:
        Game();
        void run();
};

#endif /* GAME_H */
