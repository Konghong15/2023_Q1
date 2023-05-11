#pragma once

#include <map>
#include "eSceneType.h"

namespace hockman
{
	class Scene;
	class Object;

	class SceneManager
	{
	public:
		static SceneManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Frame();
		void Release();

		void ChangeScene(eSceneType sceneType);
		void Register(eSceneType type, Scene* scene);

		inline const Scene& GetCurScene() const;
		void SpawnCurScene(Object* obj);

	private:
		SceneManager();
		~SceneManager() = default;

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