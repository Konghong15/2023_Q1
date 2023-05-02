#pragma once

#include <map>

namespace hockman
{
	class Scene;
	enum class eSceneType;

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

		inline const Scene* GetCurScene() const;

	private:
		SceneManager();
		~SceneManager() = default;

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