#include "Ground.h"

namespace hockman
{
	Ground::Ground(hRectangle rectangle, eSpriteType spriteType)
		: Object(rectangle, spriteType, eObjectType::GROUND)
	{
	}

	void Ground::Frame()
	{
	}
}