#pragma once

#include "./fmod/fmod.h"
#include "./fmod/fmod.hpp"
#include "./fmod/fmod_errors.h"

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