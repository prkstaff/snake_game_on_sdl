#include "Sound.h"
#include <iostream>

Sound* Sound::instance(){
    if(sound_ == NULL){
        sound_ = new Sound();
    }
    return sound_;
};
Sound::Sound(){
    //Load sound effects
    chomp_sound = Mix_LoadWAV( "src/aud_chomp.wav" );
    if( chomp_sound == NULL ) {
        printf( "Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
    }
};
Sound::~Sound(){
    Mix_FreeChunk(chomp_sound);
};
void Sound::play_chomp_sound(){
    Mix_PlayChannel( -1, chomp_sound, 0 );
};
Sound * Sound::sound_ = 0;
