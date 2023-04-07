#include "Monster.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ColliderManager.h"

namespace hongpireSurvivors
{
	Monster::Monster(COORD pos, COORD size, eSpriteType spriteType, bool isLeft)
		: Object(pos, size, spriteType, eObjectType::ENEMY, isLeft)
		, mCanMove(true)
		, mElapsed(0.f)
	{
	}

	void Monster::Frame()
	{
		const float DELTA_TIME = TimeManager::GetInstance()->GetDeltaTime();
		mElapsed += DELTA_TIME;

		handleCollision();

		if (!mIsVaild)
		{
			return;
		}

		handleMove();
		handleDirection();
	}

	void Monster::handleCollision()
	{
		int flag = mCollider->GetEnterBitFlag();
		int mask = static_cast<int>(eObjectType::PROJECTILE);

		if ((flag & mask) != 0)
		{
			mIsVaild = false;
		}
	}

	void Monster::handleDirection()
	{
		if (mPos.X <= 0)
		{
			mIsLeft = false;
			mPos.X = 0;
		}
		else if (mPos.X == 400 - mSize.X)
		{
			mIsLeft = true;
			mPos.X = 400 - mSize.X;
		}
	}
}