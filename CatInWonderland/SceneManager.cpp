#include <cassert>

#include "SceneManager.h"
#include "WinApp.h"
#include "Scene.h"
#include "GameScene.h"

namespace catInWonderland
{
	SceneManager* SceneManager::mInstance = nullptr;

	SceneManager* SceneManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SceneManager();
			mInstance->init();
		}

		return mInstance;
	}

	void SceneManager::DeleteInstance()
	{
		mInstance->release();
		delete mInstance;
		mInstance = nullptr;
	}

	void SceneManager::init()
	{
		// cur Scene setting
		mCurScene = new GameScene();
		mCurScene->Enter();
		// init
	}

	void SceneManager::release()
	{
		mCurScene->Exit();

		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end();)
		{
			delete (iter->second);
			iter = mSceneMap.erase(iter);
		}

		mSceneMap.clear();
	}

	void SceneManager::Frame()
	{
		mCurScene->Frame();
	}

	void SceneManager::ChangeScene(eSceneType sceneType)
	{
		auto iter = mSceneMap.find(sceneType);
		assert(iter != mSceneMap.end());

		mCurScene->Exit();
		mCurScene = iter->second;
		mCurScene->Enter();
	}

	void SceneManager::SpawnCurScene(Object* obj)
	{
		assert(mCurScene != nullptr);
		mCurScene->Spawn(obj);
	}
}