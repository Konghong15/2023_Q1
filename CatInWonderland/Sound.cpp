//#include "Sound.h"
//
//#define NULL ((void*)0)
//
//namespace catInWonderland
//{
//	Sound::Sound(const char* fileName, bool isRecursive)
//		: mbRecursive(isRecursive)
//	{
//		FMOD::System_Create(&mSystem);
//		mSystem->init(32, FMOD_INIT_NORMAL, 0);
//
//	/*	if (isRecursive)
//		{
//			mSystem->createSound(fileName, FMOD_LOOP_NORMAL, NULL, &mSound);
//			mSound->setMode(FMOD_LOOP_NORMAL);
//		}
//		else
//		{
//			mSystem->createSound(fileName, FMOD_LOOP_OFF, NULL, &mSound);
//			mSound->setMode(FMOD_LOOP_OFF);
//		}*/
//	}
//
//	Sound::~Sound()
//	{
//		if (mSound != nullptr)
//		{
//			mSound->release();
//		}
//		if (mSystem != nullptr)
//		{
//			mSystem->close();
//			mSystem->release();
//		}
//	}
//
//	void Sound::Start()
//	{/*
//		mSystem->playSound(mSound, NULL, false, &mChannel);*/
//	}
//
//	void Sound::Stop()
//	{
//		mChannel->stop();
//	}
//}