#ifndef _SOUND_
#define _SOUND_
#include <SDL2/SDL_mixer.h>
class Sound{
    public:
        static Sound* instance();
        void play_chomp_sound();
    private:
        static Sound* sound_;
        Mix_Chunk* chomp_sound;
        Sound();
        ~Sound();
};
#endif /* ifndef _SOUND_
class Sound{
    public:
        static Sound instance();
    private:
        static Sound _sound;
}; */
