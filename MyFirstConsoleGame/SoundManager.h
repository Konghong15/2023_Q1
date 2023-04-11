#pragma once

#include <map>

namespace hongpireSurvivors
{
	enum class eSound
	{
		PLAYER_DEATH,
		PLAYER_HIT,
		PLAYER_JUMP,
		PLAYER_THROW,
		BGM,
		GAME_START,
		MONSTER_HIT,
		MONSTER_DEATH
	};

	class Sound;

	class SoundManager
	{
	public:
		static SoundManager* GetInstance();
		static void DeleteInstance();

		void Play(eSound sound);
		void Stop(eSound sound);

	private:
		SoundManager();
		~SoundManager();

		void load();

	private:
		static SoundManager* mInstance;

		std::map<eSound, Sound*> mSoundMap;
	};

}