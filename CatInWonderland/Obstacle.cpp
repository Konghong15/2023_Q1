#include "Obstacle.h"

namespace catInWonderland
{
	Obstacle::Obstacle(const ObjectInfo& objectInfo, size_t boardX, size_t boardY)
		: BoardObject(objectInfo, boardX, boardY)
	{
	}

	Obstacle::Obstacle(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, eObjectType::Obstacle, layerType, boardX, boardY, bLeft)
	{
	}

	void Obstacle::Update()
	{
	}
}
