#include "Tile.h"
#include "RenderManager.h"

namespace catInWonderland
{
	Tile::Tile(const ObjectInfo& objectInfo, size_t boardX, size_t boardY)
		: BoardObject(objectInfo, boardX, boardY)
	{
	}

	Tile::Tile(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, eObjectType::Tile, layerType, boardX, boardY, bLeft)
	{
	}

	void Tile::Update()
	{

	}
}

