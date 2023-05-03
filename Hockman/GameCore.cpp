#include "GameCore.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "SpriteManager.h"
//#include "SoundManager.h"
#include "SceneManager.h"
#include "RenderManager.h"
#include "ColliderManager.h"

namespace hockman
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
		// non-init manager
		InputManager::GetInstance();
		TimeManager::GetInstance();

		// init Manager
		SpriteManager::GetInstance()->Init();
		//SoundManager::GetInstance()->Init();
		SceneManager::GetInstance()->Init();
		RenderManager::GetInstance()->Init();
		ColliderManager::GetInstance()->Init();
	}

	void GameCore::Frame()
	{
		InputManager::GetInstance()->Frame();
		TimeManager::GetInstance()->Frame();

		SceneManager::GetInstance()->Frame();
		ColliderManager::GetInstance()->Frame();

		RenderManager::GetInstance()->Render();
	}

	void GameCore::Release()
	{
		// Release
		RenderManager::GetInstance()->Release();
		//SoundManager::GetInstance()->Release();
		SpriteManager::GetInstance()->Release();
		SceneManager::GetInstance()->Release();

		// Delete
		RenderManager::DeleteInstance();
		SceneManager::DeleteInstance();
		//SoundManager::DeleteInstance();
		SpriteManager::DeleteInstance();
		TimeManager::DeleteInstance();
		InputManager::DeleteInstance();
		ColliderManager::GetInstance()->Release();
	}
}