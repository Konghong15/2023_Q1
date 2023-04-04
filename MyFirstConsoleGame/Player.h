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
		int mElapsed;
		bool mCanMove;
	};
}