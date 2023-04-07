#pragma once

#include "Monster.h"

namespace hongpireSurvivors
{
	class Bat : public Monster
	{
	public:
		Bat(COORD pos, COORD size, eSpriteType spriteType, bool isLeft = true);
		virtual ~Bat() = default;

		virtual void Frame() override;

	protected:
		virtual void handleMove() override;
		void handleAttack();

	private:
		bool mCanAttack;
		float mAttackElapsed;
		float mDropElapsed;
		bool mIsDrop;
	};
}