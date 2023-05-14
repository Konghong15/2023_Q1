#pragma once

#include <cassert>
#include <map>

#include "eSceneType.h"

namespace catInWonderland
{
	class Scene;
	class Object;

	class SceneManager
	{
	public:
		static SceneManager* GetInstance();
		static void DeleteInstance();

		void Frame();
		void Rotate(bool bLeft);

		void ChangeScene(eSceneType sceneType);
		void SpawnCurScene(Object* obj);

		inline const Scene& GetCurScene() const;

	private:
		SceneManager() = default;
		~SceneManager() = default;

		void init();
		void release();

	private:
		static SceneManager* mInstance;

		std::map<eSceneType, Scene*> mSceneMap;
		Scene* mCurScene;
	};

	const Scene& SceneManager::GetCurScene() const
	{
		return *mCurScene;
	}

}