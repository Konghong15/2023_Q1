#pragma once

#include "Scene.h"

namespace catInWonderland  
{
	class GameScene : public Scene
	{
	public:
		GameScene();
		virtual ~GameScene() = default;

		virtual void Enter() override;
		virtual void Frame() override;

	private:
		const float mRotationEnd;
		bool mbRotate;
		bool mbLeft;
		float mElapsed;
	};
}