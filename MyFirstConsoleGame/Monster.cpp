#include "Monster.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ColliderManager.h"

namespace hongpireSurvivors
{
	Monster::Monster(COORD pos, COORD size, eSpriteType spriteType)
		: Object(pos, size, spriteType, eObjectType::ENEMY, true)
		, mCanMove(true)
		, mIsLeft(true)
		, mElapsed(0.f)
	{
	}

	void Monster::Frame()
	{
		if (!mCanMove)
		{
			mElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mElapsed >= 0.01f)
			{
				mElapsed = 0.0f;
				mCanMove = true;
			}

			return;
		}

		int flag = mCollider->GetStayBitFlag();
		int mask = static_cast<int>(eObjectType::PROJECTILE);
		if ((flag & mask) != 0)
		{
			mIsVaild = false;
			return;
		}

		if (mPos.X == 0)
		{
			mIsLeft = false;
		}
		else if (mPos.X == 400 - mSize.X)
		{
			mIsLeft = true;
		}

		if (mIsLeft)
		{
			--mPos.X;
		}
		else
		{
			++mPos.X;
		}

		mCanMove = false;
	}
}