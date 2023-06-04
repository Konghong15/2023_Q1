#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class Stage10 :public GameScene
	{
	public:
		Stage10(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage10() = default;

		virtual void Enter() override;


	protected:
		virtual void CreateBoardObject() override;
	};
}

