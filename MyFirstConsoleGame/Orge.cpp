#include "Orge.h"
#include "Scene.h"
#include "TimeManager.h"
#include "ObjectManager.h"
#include "Helper.h"

namespace hongpireSurvivors
{
	Orge::Orge(COORD pos, COORD size, int minX, int maxX, bool isLeft)
		: Monster(pos, size, eSpriteType::BOSS_0_IDLE, minX, maxX, 5, isLeft)
		, mCanAttack(false)
		, mIsJump(false)
		, mDropElapsed(0.f)
		, mAttackElapsed(0.f)
		, mArrival(0)
	{
	}

	void Orge::Frame()
	{
		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
		handleAttack();
		handleJump();
	}

	void Orge::handleMove()
	{
		if (!mIsJump)
		{
			return;
		}
		if (mArrival == mPos.X)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		if (mElapsed >= ONE_FRAME_TIME)
		{
			mElapsed -= ONE_FRAME_TIME;

			if (abs(mPos.X - mArrival) > 5)
			{
				mPos.X += mArrival > mPos.X ? MONSTER_SPEED_HIGH : -MONSTER_SPEED_HIGH;
			}
			else
			{
				mPos.X += mArrival > mPos.X ? MONSTER_SPEED_LOW : -MONSTER_SPEED_LOW;
			}
		}
	}

	void Orge::handleJump()
	{
		if (!mIsJump)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mDropElapsed += DELTA_TIME;

		if (mDropElapsed >= ONE_FRAME_TIME)
		{
			mDropElapsed -= ONE_FRAME_TIME;


			if (mJumpForce > 0.25f)
			{
				mPos.Y -= MONSTER_SPEED_HIGH;
				mPos.Y = Helper::Clamp(0, 67 - mSize.Y, mPos.Y);
				mSpriteType = eSpriteType::BOSS_0_JUMP;
			}
			else if (mJumpForce > 0.f)
			{
				mPos.Y -= 1;
				mPos.Y = Helper::Clamp(0, 67 - mSize.Y, mPos.Y);
				mSpriteType = eSpriteType::BOSS_0_JUMP;
			}
			else if (mJumpForce > -0.1f)
			{
				mPos.Y += 1;
			}
			else
			{
				mPos.Y += MONSTER_SPEED_HIGH;
			}
		}

		mJumpForce -= DELTA_TIME * 1.5f;

		if (mPos.Y + mSize.Y > 67)
		{
			mSpriteType = eSpriteType::BOSS_0_IDLE;
			--mPos.Y;
			mIsJump = false;
			mJumpForce = 0.0f;
		}
	}

	void Orge::handleAttack()
	{
		if (mIsJump)
		{
			return;
		}

		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mAttackElapsed += DELTA_TIME;

		if (mAttackElapsed < ONE_FRAME_TIME * 30)
		{
			return;
		}

		mAttackElapsed = 0.f;

		mArrival = Scene::mScene->GetPlayer().GetPos().X;
		mArrival = Helper::Clamp(0, Helper::MAP_WIDTH - 30, mArrival);
		mJumpForce = 0.75f;
		mIsJump = true;
		mIsLeft = mArrival > mPos.X ? false : true;
	}
}