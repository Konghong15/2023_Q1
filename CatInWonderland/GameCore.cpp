#include "GameCore.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteManager.h"
//#include "SoundManager.h"
#include "SceneManager.h"
#include "RenderManager.h"

namespace catInWonderland
{
	GameCore* GameCore::mInstance = nullptr;

	GameCore* GameCore::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new GameCore();
		}

		return mInstance;
	}

	void GameCore::DeletInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}

	void GameCore::Init()
	{
		TimeManager::GetInstance();
		InputManager::GetInstance();
		SpriteManager::GetInstance();
		//SoundManager::GetInstance()->Init();
		SceneManager::GetInstance();
		RenderManager::GetInstance();
	}

	void GameCore::Frame()
	{
		InputManager::GetInstance()->Frame();
		TimeManager::GetInstance()->Frame();
		SceneManager::GetInstance()->Frame();
		RenderManager::GetInstance()->Render();
	}

	void GameCore::Release()
	{
		RenderManager::DeleteInstance();
		SceneManager::DeleteInstance();
		//SoundManager::DeleteInstance();
		SpriteManager::DeleteInstance();
		TimeManager::DeleteInstance();
		InputManager::DeleteInstance();
	}
}