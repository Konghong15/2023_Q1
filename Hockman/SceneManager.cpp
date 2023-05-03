#include <cassert>

#include "SceneManager.h"
#include "Scene.h"
#include "GameScene.h"
#include "eSceneType.h"

namespace hockman
{
	SceneManager* SceneManager::mInstance = nullptr;

	SceneManager* SceneManager::GetInstance()
	{
		if (mInstance == nullptr)
		{
			mInstance = new SceneManager();
		}

		return mInstance;
	}

	void SceneManager::DeleteInstance()
	{
		delete mInstance;
		mInstance = nullptr;
	}


	SceneManager::SceneManager()
		: mCurScene(nullptr)
	{
	}

	void SceneManager::Init()
	{
		// init
		mSceneMap.emplace(eSceneType::GAME, new GameScene(1920, 1000));


		// init scene
		auto iter = mSceneMap.find(eSceneType::GAME);
		assert(iter != mSceneMap.end());
		mCurScene = iter->second;
		mCurScene->Enter();
	}

	void SceneManager::Frame()
	{
		mCurScene->Frame();
	}

	void SceneManager::Release()
	{
		mCurScene->Exit();

		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end();)
		{
			delete (iter->second);
			iter = mSceneMap.erase(iter);
		}

		mSceneMap.clear();
	}

	void SceneManager::ChangeScene(eSceneType sceneType)
	{
		auto iter = mSceneMap.find(sceneType);
		assert(iter != mSceneMap.end());

		mCurScene->Exit();
		mCurScene = iter->second;
		mCurScene->Enter();
	}

	void SceneManager::Register(eSceneType type, Scene* scene)
	{
		mSceneMap.emplace(type, scene);
	}
}