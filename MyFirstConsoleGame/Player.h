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
		void handleMove();
		void handleJump();
		void handleAttack();

	private:
		float mElapsed;
		float mAttackElapsed;
		float mDropElapsed;
		float mAniElapsed;
		float mJumpForce;
		bool mCanMove;
		bool mCanAttack;
		bool mCanJump;
	};
}