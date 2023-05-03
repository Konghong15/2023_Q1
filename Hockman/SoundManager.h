//#pragma once
//
//#include <map>
//
//namespace hockman
//{
//	enum class eSound
//	{
//		PLAYER_DEATH,
//		PLAYER_HIT,
//		PLAYER_JUMP,
//		PLAYER_THROW,
//		TITLE_BGM,
//		GAME_BGM,
//		ENDING_BGM,
//		GAME_START,
//		MONSTER_HIT,
//		MONSTER_DEATH
//	};
//
//	class Sound;
//
//	class SoundManager
//	{
//	public:
//		static SoundManager* GetInstance();
//		static void DeleteInstance();
//
//		void Init();
//		void Release();
//
//		void Play(eSound sound);
//		void Stop(eSound sound);
//
//	private:
//		SoundManager() = default;
//		~SoundManager() = default;
//
//	private:
//		static SoundManager* mInstance;
//
//		std::map<eSound, Sound*> mSoundMap;
//	};
//
//}