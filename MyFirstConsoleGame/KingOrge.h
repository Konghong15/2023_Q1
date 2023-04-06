#pragma once

#include "Object.h"

namespace hongpireSurvivors
{
	class KingOrge : public Object
	{
	public:
		KingOrge(COORD pos, COORD size, eSpriteType spriteType);
		virtual ~KingOrge() = default;

		virtual void Frame() override;
	};
}