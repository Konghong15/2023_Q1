#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage08 :public GameScene
	{
	public:
		Stage08(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage08() = default;
	
		virtual void Enter() override;


	protected:
		virtual void CreateBoardObject() override;
	};
}

