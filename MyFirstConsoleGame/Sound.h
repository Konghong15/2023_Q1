#pragma once

#include "./fmod/fmod.h"
#include "./fmod/fmod.hpp"
#include "./fmod/fmod_errors.h"

#pragma comment(lib, "./fmod/fmod_vc.lib")
#pragma comment(lib, "./fmod/fmodL_vc.lib")

namespace hongpireSurvivors
{
	class Sound
	{
	public:
		Sound(const char* fileName, bool isRecursive = false);
		~Sound();

		void Start();
		void Stop();

	private:
		FMOD::System* mSystem;
		FMOD::Sound* mSound;
		FMOD::Channel* mChannel;

		bool mbRecursive;
	};
}