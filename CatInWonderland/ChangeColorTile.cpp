#include "ChangeColorTile.h"

namespace catInWonderland
{
	ChangeColorTile::ChangeColorTile(const ObjectInfo& objectInfo, size_t boardX, size_t boardY, bool bRed)
		: BoardObject(objectInfo, boardX, boardY)
		, mbRed(bRed)
	{
	}

	ChangeColorTile::ChangeColorTile(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool bRed, bool bLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, (bRed ? eObjectType::RedChangeColorTile : eObjectType::BlueChangeColorTile), layerType, boardX, boardY, bLeft)
		, mbRed(bRed)
	{
	}

	void ChangeColorTile::Update()
	{

	}
}