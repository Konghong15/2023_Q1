#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class Monster : public Object
	{
	public:
		Monster(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~Monster() = default;

		virtual void Frame() override;

	private:
		float mElapsed;
		bool mCanMove;
		bool mIsLeft;
	};
}