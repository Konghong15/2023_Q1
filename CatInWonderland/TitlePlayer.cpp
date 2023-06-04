#include "TitlePlayer.h"
#include "TimeManager.h"
#include "SpriteManager.h"

namespace catInWonderland
{
	TitlePlayer::TitlePlayer(hRectangle worldRectangle, eLayerType layerType)
		: Object(worldRectangle, SpriteManager::GetInstance()->GetSpriteRectangle(eAnimationType::PlayerIdle, 0), eSpriteType::Player, eObjectType::None, layerType, false)
		, mAnimator(SpriteManager::GetInstance()->GetAnimator(eAnimationType::PlayerIdle))
		, mbExcute(false)
	{
	}

	void TitlePlayer::Update(float deltaTime)
	{
		mAnimator.Update(this);

		if (mbExcute)
		{
			const float DELTA_TIME = deltaTime * 300;
			MoveInWorld(DELTA_TIME, 0);
		}
	}
};
