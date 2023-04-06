#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class FlyingOrge : public Object
	{
	public:
		FlyingOrge(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~FlyingOrge() = default;

		virtual void Frame() override;
	};
}