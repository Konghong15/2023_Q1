#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage03:public GameScene
	{
	public:
		Stage03(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage03() = default;

		virtual void Enter() override;
		virtual void Update() override;
	};
}

