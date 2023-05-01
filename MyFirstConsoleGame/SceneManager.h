#pragma once

#include <map>

namespace hongpireSurvivors
{
	class Scene;
	enum class eSceneType;

	class SceneManager
	{
	public:
		static SceneManager* GetInstance();
		static void DeleteInstance();

		void Init();
		void Enter(eSceneType sceneType);
		void Frame();

		void OnRegister(eSceneType type, Scene* scene);
		inline const Scene* GetCurScene() const;

	private:
		SceneManager() = default;
		~SceneManager();

	private:
		static SceneManager* mInstance;

		std::map<eSceneType, Scene*> mSceneMap;
		Scene* mCurScene;
	};

	const Scene* SceneManager::GetCurScene() const
	{
		return mCurScene;
	}
}