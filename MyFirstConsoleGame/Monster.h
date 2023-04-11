#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Monster : public Object
	{
	public:
		Monster(COORD pos, COORD size, eSpriteType spriteType, int minX, int maxX, int hp = 1, bool isLeft = true);
		virtual ~Monster() = default;

		virtual void Frame() override;
		virtual void Render() override;

	protected:
		virtual void handleCollision();
		virtual void handleDirection();
		virtual void handleMove() = 0;

	protected:
		const COORD START_POS;

		int mHp;
		float mElapsed;
		int mMinX;
		int mMaxX;
	};
}