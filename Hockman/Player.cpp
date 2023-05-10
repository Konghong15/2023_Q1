#include "Player.h"
#include "InputManager.h"
#include "TimeManager.h"
#include "RenderManager.h"
#include "PlayerIdle.h"
#include "Collider.h"

namespace hockman
{
	Player::Player(hRectangle rectangle, hRectangle uvRectangle, eSpriteType spriteType, eObjectType objectType, float moveSpeed)
		: Object(rectangle, spriteType, objectType)
		, mUVRectangle(uvRectangle)
		, mMoveSpeed(moveSpeed)
		, mPlayerState(new PlayerIdle())
		, mIsRight(true)
		, mGravity(5000.f)
	{
		mPlayerState->Enter(this);
	}

	void Player::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();

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