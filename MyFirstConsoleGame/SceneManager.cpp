#include <cassert>

#include "SceneManager.h"
#include "Scene.h"
#include "eSceneType.h"

namespace hongpireSurvivors
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

	void SceneManager::Init()
	{
		auto iter = mSceneMap.find(eSceneType::TITLE);
		assert(iter != mSceneMap.end());

		mCurScene = iter->second;
		mCurScene->Enter();
	}

	void SceneManager::Enter(eSceneType sceneType)
	{
		auto iter = mSceneMap.find(sceneType);
		assert(iter != mSceneMap.end());

		mCurScene->Exit();
		mCurScene = iter->second;
		mCurScene->Enter();
	}

	void SceneManager::Frame()
	{
		mCurScene->Frame();
	}

	void SceneManager::OnRegister(eSceneType type, Scene* scene)
	{
		mSceneMap.insert({ type, scene });
	}

	SceneManager::~SceneManager()
	{
		mCurScene->Exit();

		for (auto iter = mSceneMap.begin(); iter != mSceneMap.end();)
		{
			delete (iter->second);
			iter = mSceneMap.erase(iter);
		}
	}
}