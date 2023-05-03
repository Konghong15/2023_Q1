#pragma once

#include "Scene.h"

namespace hockman
{
	class GameScene : public Scene
	{
	public:
		GameScene(size_t width, size_t height);
		virtual ~GameScene() = default;

		virtual void Enter() override;
	};
}