#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage05 :public GameScene
	{
	public:
		Stage05(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage05() = default;
		
		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	protected:
		virtual void CreateBoardObject() override;
		virtual void CreateTileObject() override;
	};
}

