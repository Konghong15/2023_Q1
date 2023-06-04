#include "Butterfly.h"
#include "PlayerMove.h"
#include "TimeManager.h"
#include "SpriteManager.h"
#include "SceneManager.h"
#include "ChangeColorTile.h"

namespace catInWonderland
{
	Butterfly::Butterfly(const ObjectInfo& objectInfo, Object* interactionObjectOrNull, eLayerType layerType, float maxOffset, bool bRed, const Animator& animator)
		: Object(objectInfo)
		, mInteractionObjectOrNull(interactionObjectOrNull)
		, mMaxOffset(maxOffset)
		, mbRed(bRed)
		, mAnimator(animator)
	{
	}

	Butterfly::Butterfly(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eObjectType objectType, Object* interactionObjectOrNull, eLayerType layerType, float maxOffset, bool bRed, bool bLeft, const Animator& animator)
		: Object(worldRectangle, spriteRectangle, sprite, eObjectType::Butterfly, layerType, bLeft)
		, mInteractionObjectOrNull(interactionObjectOrNull)
		, mMaxOffset(maxOffset)
		, mbRed(bRed)
		, mAnimator(animator)
	{
	}

	void Butterfly::Update()
	{
		mAnimator.Update(this);

		if (mInteractionObjectOrNull == nullptr)
		{
			return;
		}

		Vector2 distance;
		if (mbLeft)
		{
			distance = mInteractionObjectOrNull->GetWorldRectangle().GetTopRight() - mWorldRectangle.GetTopRight();
		}
		else
		{
			distance = mInteractionObjectOrNull->GetWorldRectangle().GetTopLeft() - mWorldRectangle.GetTopLeft();
		}

		if (distance.GetMagnitude() > mMaxOffset)	//플레이어를 쫒아감  
		{
			float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime() / 0.2f;
			MoveInWorld(distance.GetX() * DELTA_TIME, distance.GetY() * DELTA_TIME);
		}
	}

	void Butterfly::InvertColor()
	{
		mbRed ^= true;

		if (mbRed)
		{
			mAnimator = SpriteManager::GetInstance()->GetAnimator(eAnimationType::RedButterfly);
		}
		else
		{
			mAnimator = SpriteManager::GetInstance()->GetAnimator(eAnimationType::BlueButterfly);
		}
		mSpriteRectangle = mAnimator.GetSpriteRectangle(0);
	}

	void Butterfly::SetIsRed(bool bRed)
	{
		mbRed = bRed;

		if (mbRed)
		{
			mAnimator = SpriteManager::GetInstance()->GetAnimator(eAnimationType::RedButterfly);
		}
		else
		{
			mAnimator = SpriteManager::GetInstance()->GetAnimator(eAnimationType::BlueButterfly);
		}

		mSpriteRectangle = mAnimator.GetSpriteRectangle(0);
	}
}
