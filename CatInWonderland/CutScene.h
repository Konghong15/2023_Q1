#pragma once

#include "Scene.h"

namespace catInWonderland
{
	class CutScene : public Scene
	{
	public:
		CutScene(eSceneType sceneType);
		virtual ~CutScene() = default;

		virtual eSceneType HandleScene() = 0;
		virtual void Enter();
		virtual void Exit();

	protected:
		Object* mMap;
		Button* mSpaceButton;
	};
}

