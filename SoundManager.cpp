#include "SoundManager.h"
#include <iostream>

SoundManager::SoundManager()
{
    if (Mix_OpenAudio(48000, AUDIO_S16SYS, 2, 4096) == -1)
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

bool SoundManager::loadMusicAndSFX(const char* fileName,
    std::string id, int type)
{
    if (type == 1)
    {
        Mix_Music* music = Mix_LoadMUS(fileName);
        if (music == 0)
        {
            std::cout << "Could not load music "
                << Mix_GetError() << std::endl;
            return false;
        }
        s_mMusic[id] = music;
        return true;
    }
    else
    {
        if (type == 0)
        {
            Mix_Chunk* chunk = Mix_LoadWAV(fileName);
            if (chunk == 0)
            {
                std::cout << "Could not load sfx" << Mix_GetError() << std::endl;
                return false;
            }
            s_mSfxs[id] = chunk;
            return true;
        }
    }
}

void SoundManager::playBackgroundMusic(std::string id,
    int loop, int ms)
{
    if (Mix_FadeInMusic(s_mMusic[id], loop, ms))
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

void SoundManager::playSFX(std::string id,
    int loop, int ms)
{
    if (Mix_FadeInChannel(-1, s_mSfxs[id], loop, ms))
    {
        std::cout << Mix_GetError() << std::endl;
    }
}

SoundManager::~SoundManager()
{
    delete instance;
    instance = nullptr;
    std::cout << "Destructor of SoundManager is called" << std::endl;
}

SoundManager* SoundManager::instance = nullptr;