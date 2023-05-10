#pragma once

#include "Object.h"

namespace hockman
{
	class Ground final : public Object
	{
	public:
		Ground(hRectangle rectangle, eSpriteType spriteType);
		~Ground() = default;

		virtual void Frame() override;
		// virtual void Render() override;
	};
}