//#include "SceneManager.h"
//#include "Scene.h"
//
//namespace hongpireSurvivors
//{
//	SceneManager* SceneManager::mInstance = nullptr;
//
//	SceneManager* SceneManager::GetInstance()
//	{
//		if (mInstance == nullptr)
//		{
//			mInstance = new SceneManager();
//		}
//
//		return mInstance;
//	}
//
//	void SceneManager::DeleteInstance()
//	{
//		delete mInstance;
//		mInstance = nullptr;
//	}
//
//	void SceneManager::Frame()
//	{
//		curScene->Frame();
//	}
//
//	void SceneManager::Enter(eSceneType sceneType)
//	{
//
//	}
//
//	SceneManager::SceneManager()
//	{
//	}
//
//	SceneManager::~SceneManager()
//	{
//		delete mTitle;
//		delete mEnding;
//		delete mGame;
//	}
//}