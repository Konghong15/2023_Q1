#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage09 :public GameScene
	{
	public:
		Stage09(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage09() = default;

		virtual void Enter() override;

	protected:
		virtual void CreateBoardObject() override;
	};
}

