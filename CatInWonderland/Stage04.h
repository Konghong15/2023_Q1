#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage04 :public GameScene
	{
	public:
		Stage04(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage04() = default;

		virtual void Enter() override;
		virtual void Update() override;
	};
}

