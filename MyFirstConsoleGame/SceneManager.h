//#pragma once
//
//namespace hongpireSurvivors
//{
//	enum class eSceneType
//	{
//		TITLE,
//		STAGE_1,
//		BOSS_ROOM,
//		ENDING
//	};
//
//	class Scene;
//
//	class SceneManager
//	{
//	public:
//		static SceneManager* GetInstance();
//		static void DeleteInstance();
//
//		void Frame();
//
//	private:
//		void Enter(eSceneType sceneType);
//
//	private:
//		SceneManager();
//		~SceneManager();
//
//	private:
//		static SceneManager* mInstance;
//
//		Scene* mTitle;
//		Scene* mGame;
//		Scene* mBossRoom;
//		Scene* mEnding;
//
//		Scene* curScene;
//	};
//}