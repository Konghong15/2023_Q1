#pragma once

#include "GameScene.h"

namespace catInWonderland
{
	class GuideButton;

	class Stage02 :public GameScene
	{
	public:
		Stage02(const std::vector<BoardObjectInfo>& boardObjectInfos);
		virtual ~Stage02() = default;

		virtual void Enter() override;
		virtual void Update() override;
		virtual void Exit() override;

	private:
		bool mbPlayerMoveCheck;
		float mGuideButtonInterval;
		GuideButton* mGuideButton[2];
	};
}