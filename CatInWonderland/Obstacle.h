#pragma once

#include "BoardObject.h"

namespace catInWonderland
{
	class Obstacle : public BoardObject
	{
	public:
		Obstacle(const ObjectInfo& objectInfo, size_t boardX, size_t boardY);
		Obstacle(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft = true);
		virtual ~Obstacle() = default;

		virtual void Update(float deltaTime);
	};
}