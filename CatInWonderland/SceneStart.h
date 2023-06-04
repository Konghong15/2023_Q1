#pragma once

#include "Scene.h"
#include "SceneManager.h"

namespace catInWonderland
{
	class Button;
	class TitlePlayer;
	class Butterfly;

	class SceneStart : public Scene
	{
	public:
		virtual void Enter() override;
		virtual eSceneType HandleScene() override;
		virtual void Update() override;
		virtual void Exit() override;

	public:
		SceneStart();
		virtual ~SceneStart() = default;

	private:
		Button* mStartButton;
		Button* mChallengeButton;
		Button* mExitButton;
		TitlePlayer* mTitlePlayer;
		Butterfly* mTitleButterfly;

		float mAlphaElapsed;
		bool mbAlpha;
	};
}