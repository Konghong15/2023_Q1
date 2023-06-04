#pragma once

#include <cassert>
#include <map>

#include "eSceneType.h"
#include "Scene.h"

namespace catInWonderland
{
	class Scene;

	class SceneManager final
	{
	public:
		SceneManager() = default;
		~SceneManager();
		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;

		void Update(float deltaTime);

		inline void RegisterScene(eSceneType sceneType, Scene* scene);
		inline void SetCurScene(eSceneType sceneType);

		inline const Scene& GetCurrentScene() const;

	private:
		std::map<eSceneType, Scene*> mSceneMap;
		Scene* mCurrentScene;
	};

	void SceneManager::RegisterScene(eSceneType sceneType, Scene* scene)
	{
		assert(mSceneMap.find(sceneType) == mSceneMap.end());
		mSceneMap.emplace(sceneType, scene);
	}

	const Scene& SceneManager::GetCurrentScene() const
	{
		return *mCurrentScene;
	}

	void SceneManager::SetCurScene(eSceneType sceneType)
	{
		auto iter = mSceneMap.find(sceneType);
		assert(iter != mSceneMap.end());

		mCurrentScene = iter->second;
		mCurrentScene->Enter();
	}
}