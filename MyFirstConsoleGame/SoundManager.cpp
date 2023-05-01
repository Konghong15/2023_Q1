#include <cassert>

#include "SoundManager.h"
#include "Sound.h"

namespace hongpireSurvivors
{
	SoundManager* SoundManager::mInstance = nullptr;

	SoundManager* SoundManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SoundManager();
		}

		return mInstance;
	}

	void SoundManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	SoundManager::SoundManager()
	{
		load();
	}

	SoundManager::~SoundManager()
	{
		for (auto iter = mSoundMap.begin(); iter != mSoundMap.end(); ++iter)
		{
			delete (iter->second);
		}
	}

	void SoundManager::Play(eSound sound)
	{
		auto iter = mSoundMap.find(sound);
		assert(iter != mSoundMap.end());

		(iter->second)->Start();
	}
	void SoundManager::Stop(eSound sound)
	{
		auto iter = mSoundMap.find(sound);
		assert(iter != mSoundMap.end());

		(iter->second)->Stop();
	}

	void SoundManager::load()
	{
		mSoundMap.emplace(eSound::TITLE_BGM, new Sound("./sound/bgm.mp3", true));
		mSoundMap.emplace(eSound::GAME_BGM, new Sound("./sound/bgm.mp3", true));
		mSoundMap.emplace(eSound::ENDING_BGM, new Sound("./sound/bgm.mp3", true));
		mSoundMap.emplace(eSound::PLAYER_DEATH, new Sound("./sound/ARTHURDEATH.wav"));
		mSoundMap.emplace(eSound::PLAYER_HIT, new Sound("./sound/ARTHURHIT.wav"));
		mSoundMap.emplace(eSound::PLAYER_JUMP, new Sound("./sound/ARTHURJUMP.wav"));
		mSoundMap.emplace(eSound::PLAYER_THROW, new Sound("./sound/ARTHURTHROW.wav"));
		mSoundMap.emplace(eSound::GAME_START, new Sound("./sound/GAMESTART.wav"));
		mSoundMap.emplace(eSound::MONSTER_HIT, new Sound("./sound/monster_hit.wav"));
		mSoundMap.emplace(eSound::MONSTER_DEATH, new Sound("./sound/monster_death.wav"));
	}
}