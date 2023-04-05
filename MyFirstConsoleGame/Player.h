#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Player : public Object
	{
	public:
		Player(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Player() = default;

		virtual void Frame() override;

	private:
		float mElapsed;
		float mAttackElapsed;
		float mJumpForce;
		bool mCanMove;
		bool mCanAttack;
		bool mCanJump;
	};
}