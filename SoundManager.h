#pragma once
#include "SDL_mixer.h"
#include "Game.h"
#include <string>
#include <map>

class SoundManager
{
public:
	bool loadMusicAndSFX(const char* fileName, std::string id, int type);

	void playSFX(std::string id, int loop, int ms = 0);
	void playBackgroundMusic(std::string id, int loop, int ms = 0);

	static SoundManager* Instance()
	{
		if (s_mInstance == 0)
		{
			s_mInstance = new SoundManager();
			return s_mInstance;
		}
		return s_mInstance;
	}
private:
	static SoundManager* s_mInstance;
	std::map<std::string, Mix_Chunk*> s_mSfxs;
	std::map<std::string, Mix_Music*> s_mMusic;

	SoundManager();
	~SoundManager();
};

