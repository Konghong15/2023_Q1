#pragma once

#include "Monster.h"

namespace hongpireSurvivors
{
	class KingOrge : public Monster
	{
	public:
		KingOrge(COORD pos, COORD size, int minX, int maxX, bool isLeft = true);
		virtual ~KingOrge() = default;

		virtual void Frame() override;

	private:
		virtual void handleMove() override;
		void handleAttack();
		void handleAnimation();

	private:
		float mAttackElapsed;
		float mSpawnElaapsed;
		float mAniElapsed;
	};
}