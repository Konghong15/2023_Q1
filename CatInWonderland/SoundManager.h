//#pragma once
//
//#include <map>
//
//namespace catInWonderland
//{
//	class Sound;
//
//	class SoundManager
//	{
//	public:
//		static SoundManager* GetInstance();
//		static void DeleteInstance();
//
//		void Play(eSound sound);
//		void Stop(eSound sound);
//
//	private:
//		SoundManager() = default;
//		~SoundManager() = default;
// 
//		void init();
//		void release();
//
//	private:
//		static SoundManager* mInstance;
//
//		std::map<eSound, Sound*> mSoundMap;
//	};
//
//}