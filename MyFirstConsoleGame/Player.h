#pragma once

#include "Object.h"


namespace hongpireSurvivors
{
	class Player : public Object
	{
		friend class Scene;

	public:
		Player(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Player() = default;

		virtual void Frame() override;
		virtual void Render() override;

	private:
		void handleMove();
		void handleJump();
		void handleAttack();
		void handleCollision();

	private:
		float mElapsed;
		float mAttackElapsed;
		float mDropElapsed;
		float mAniElapsed;
		float mJumpForce;
		float mHitElapsed;
		bool mCanAttack;
		bool mCanJump;
		bool mCanHit;
		bool mShild;
	};
}