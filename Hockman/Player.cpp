#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "PlayerIdle.h"

namespace hockman
{
	Player::Player(hRectangle rectangle, hRectangle uvRectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed)
		: Object(rectangle, spriteType, objectType)
		, mUVRectangle(uvRectangle)
		, mMoveSpeed(moveSpeed)
		, mPlayerState(new PlayerIdle())
		, mIsRight(true)
	{
		mPlayerState->Enter(this);
	}

	void Player::Frame()
	{
		mPlayerState->Update(this);
		PlayerState* nextState = mPlayerState->HandleInputOrNull(this);

		if (nextState != nullptr)
		{
			delete mPlayerState;
			mPlayerState = nextState;
			nextState->Enter(this);
		}
	}

	void Player::Render()
	{
		RenderManager::GetInstance()->Draw(mSpriteType, mRectangle, mUVRectangles->at(mAniIndex), mIsRight);
	}
}