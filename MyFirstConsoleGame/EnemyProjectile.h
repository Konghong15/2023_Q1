#pragma once

#include "Monster.h"

namespace hongpireSurvivors
{
	class EnemyProjectile : public Monster
	{
	public:
		EnemyProjectile(COORD arrivalPos, COORD pos, COORD size, eSpriteType spriteType, bool isLeft);
		virtual ~EnemyProjectile() = default;

	protected:
		virtual void handleMove() override;
		virtual void handleCollision() override;

	private:
		const COORD ARRIVAL_POS;
		const COORD START_POS;
		const float INCREASE_X;
		const float INCREASE_Y;

		unsigned int mMoveCount;
	};
}