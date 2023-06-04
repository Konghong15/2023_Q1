#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage07 :public GameScene
	{
	public:
		Stage07(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage07() = default;

		virtual void Enter() override;


	protected:
		virtual void CreateBoardObject() override;
	};
}

