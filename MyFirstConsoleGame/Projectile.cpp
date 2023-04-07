#include "Projectile.h"
#include "RenderManager.h"
#include "TimeManager.h"
#include "ColliderManager.h"

namespace hongpireSurvivors
{
	Projectile::Projectile(COORD pos, COORD size, eSpriteType spriteType, bool isLeft)
		: Object(pos, size, spriteType, eObjectType::PROJECTILE, isLeft)
		, mCanMove(true)
		, mElapsed(0.f)
	{
	}

	void Projectile::Frame()
	{
		int width = RenderManager::GetInstance()->GetScreenWidth();

		if (!mCanMove)
		{
			mElapsed += TimeManager::GetInstance()->GetDeltaTime();

			if (mElapsed >= 0.005f)
			{
				mElapsed -= 0.005f;
				mCanMove = true;
			}

			return;
		}

		int flag = mCollider->GetEnterBitFlag();
		int mask = static_cast<int>(eObjectType::ENEMY);

		if ((flag & mask) != 0)
		{
			mIsVaild = false;
			return;
		}

		if (mPos.X == 0 || mPos.X == width - 26 - mSize.X)
		{
			mIsVaild = false;
			return;
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


	// void handleMove()
	//void handleCollision()
}