#pragma once

#include "Object.h"

namespace catInWonderland
{
	class Map : public Object
	{
	public:
		Map(const ObjectInfo& objectInfo);
		Map(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, bool bLeft = true);
		virtual ~Map() = default;

		virtual void Update(float deltaTime) override;
	};
}