#pragma once

namespace catInWonderland
{
	class BoardManager;
	class InputManager;
	class RenderManager;
	class SceneManager;
	class SoundManager;
	class SpriteManager;
	class TimeManager;

	class GameCore
	{
	public:
		GameCore();
		~GameCore();
		GameCore(const GameCore&) = delete;
		GameCore& operator=(const GameCore&) = delete;

		void Frame();

	private:
		static unsigned int mInstanceCount;

		BoardManager* mBoardManager;
		InputManager* mInputManager;
		RenderManager* mRenderManager;
		SceneManager* mSceneManager;
		SoundManager* mSoundManager;
		SpriteManager* mSpriteManager;
		TimeManager* mTimeManager;
	};
}