#include <cassert>
#include <string>

#include "GameCore.h"
#include "EnumLoader.h"
#include "InputManager.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "TimeManager.h"
#include "SpriteManager.h"
#include "BoardManager.h"
#include "SoundManager.h"
#include "WinApp.h"

namespace catInWonderland
{
	unsigned int GameCore::mInstanceCount = 0u;

	GameCore::GameCore()
		: mBoardManager(new BoardManager())
		, mInputManager(new InputManager())
		, mRenderManager(new RenderManager())
		, mSceneManager(new SceneManager())
		, mSoundManager(new SoundManager())
		, mSpriteManager(new SpriteManager())
		, mTimeManager(new TimeManager())
	{
		++mInstanceCount;
		assert(mInstanceCount == 1);

		EnumLoader::LoadSound(mSoundManager);
		EnumLoader::LoadSprtie(mSpriteManager);
		EnumLoader::LoadAnimationRectangle(mSpriteManager);
		EnumLoader::LoadScene(mSceneManager);

		mSceneManager->SetCurScene(eSceneType::START);
	}

	GameCore::~GameCore()
	{
		--mInstanceCount;
		assert(mInstanceCount == 0);

		delete mBoardManager;
		delete	mInputManager;
		delete	mRenderManager;
		delete	mSceneManager;
		delete	mSoundManager;
		delete	mSpriteManager;
		delete	mTimeManager;
	}

	void GameCore::Frame()
	{
		mInputManager->Update();
		mTimeManager->Update();
		mSceneManager->Update();
		mRenderManager->Render();
	}
}