#pragma once

#include "Zombie.h"
#include "ObjectManager.h"
#include "TimeManager.h"
#include "Collider.h"
#include "Scene.h"

namespace hongpireSurvivors
{
	Zombie::Zombie(COORD pos, COORD size, eSpriteType spriteType,int minX, int maxX, bool isLeft)
		: Monster(pos, size, spriteType, minX, maxX, 2, isLeft)
	{
	}

	void Zombie::handleMove()
	{
		const Object* player = ObjectManager::GetInstance()->GetPlayerOrNull();
		COORD playerPos = player->GetPos();

		if (mElapsed >= ONE_FRAME_TIME)
		{
			mElapsed -= ONE_FRAME_TIME;

			if (mIsLeft)
			{
				if (abs(mPos.X - playerPos.X) < 100)
				{
					mPos.X -= MONSTER_SPEED_HIGH;
				}
				else
				{
					mPos.X -= MONSTER_SPEED_LOW;
				}
			}
			else
			{
				if (abs(mPos.X - playerPos.X) < 100)
				{
					mPos.X += MONSTER_SPEED_HIGH;
				}
				else
				{
					mPos.X += MONSTER_SPEED_LOW;
				}
			}
		}
	}
}