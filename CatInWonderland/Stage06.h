#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage06 :public GameScene
	{
	public:
		Stage06(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage06() = default;

		virtual void Enter() override;


	protected:
		virtual void CreateBoardObject() override;
	};
}

