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
		if (!instance)
		{
			instance = new SoundManager();
			return instance;
		}
		return instance;
	}
private:
	static SoundManager* instance;
	std::map<std::string, Mix_Chunk*> s_mSfxs;
	std::map<std::string, Mix_Music*> s_mMusic;

	SoundManager();
	~SoundManager();
};

