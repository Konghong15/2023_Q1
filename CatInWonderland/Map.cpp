#include "Map.h"
#include "RenderManager.h"

namespace catInWonderland
{
	Map::Map(const ObjectInfo& objectInfo)
		: Object(objectInfo)
	{
	}

	Map::Map(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, bool bLeft)
		: Object(worldRectangle, spriteRectangle, sprite, eObjectType::None, layerType, bLeft)
	{
	}

	void Map::Update()
	{

	}
}