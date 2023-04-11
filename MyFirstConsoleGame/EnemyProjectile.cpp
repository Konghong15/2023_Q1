#include <cmath>

#include "EnemyProjectile.h"
#include "Collider.h"

namespace hongpireSurvivors
{
	EnemyProjectile::EnemyProjectile(COORD arrivalPos, COORD pos, COORD size, eSpriteType spriteType, int minX, int maxX, bool isLeft)
		: Monster(pos, size, spriteType, minX, maxX, 1, isLeft)
		, ARRIVAL_POS(arrivalPos)
		, START_POS(pos)
		, INCREASE_X(ARRIVAL_POS.X - START_POS.X)
		, INCREASE_Y(ARRIVAL_POS.Y - START_POS.Y)
		, mMoveCount(0u)
	{
	}

	void EnemyProjectile::handleMove()
	{
		if (mElapsed < 0.01f)
		{
			return;
		}

		mElapsed -= 0.01f;
		++mMoveCount;

		int xAmonut = 0;
		int yAmount = 0;

		if (INCREASE_X == 0)
		{
			xAmonut = mMoveCount;
		}
		else if (INCREASE_Y == 0)
		{
			yAmount = mMoveCount;
		}
		else
		{
			float slope = INCREASE_Y / (float)INCREASE_X;

			if (fabs(slope) < 1.f)
			{
				yAmount = mMoveCount * slope;
				xAmonut = mMoveCount;
			}
			else
			{
				yAmount = mMoveCount;
				xAmonut = mMoveCount / slope;
			}
		}

		if (ARRIVAL_POS.X < START_POS.X)
		{
			mPos.X = START_POS.X - abs(xAmonut);
			mPos.Y = START_POS.Y + abs(yAmount);
		}
		else
		{
			mPos.X = START_POS.X + abs(xAmonut);
			mPos.Y = START_POS.Y + abs(yAmount);
		}
	}

	void EnemyProjectile::handleCollision()
	{
		if (abs(START_POS.X - mPos.X) + abs(START_POS.Y - mPos.Y) > 200)
		{
			mIsVaild = false;
			return;
		}

		Monster::handleCollision();
	}
};