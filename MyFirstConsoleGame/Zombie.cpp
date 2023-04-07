#pragma once

#include "Zombie.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Collider.h"

namespace hongpireSurvivors
{
	Zombie::Zombie(COORD pos, COORD size, eSpriteType spriteType, bool isLeft)
		: Monster(pos, size, spriteType, isLeft)
	{
	}

	void Zombie::handleMove()
	{
		const Object& player = ObjectManager::GetInstance()->GetPlayer();
		COORD playerPos = player.GetPos();

		if (mElapsed >= 0.02f)
		{
			mElapsed -= 0.02f;

			if (mIsLeft)
			{
				--mPos.X;

				if (mPos.X - playerPos.X < 100)
				{
					mPos.X -= 1;
				}
			}
			else
			{
				++mPos.X;

				if (playerPos.X - mPos.X < 100)
				{
					mPos.X += 1;
				}
			}
		}
	}
}