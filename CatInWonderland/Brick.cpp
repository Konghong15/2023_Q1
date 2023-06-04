#include "Brick.h"

namespace catInWonderland
{
	Brick::Brick(const ObjectInfo& objectInfo, size_t boardX, size_t boardY, bool bRed)
		: BoardObject(objectInfo, boardX, boardY)
		, mbRed(bRed)
	{
	}

	Brick::Brick(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool bRed, bool bLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, (bRed ? eObjectType::RedBrick : eObjectType::BlueBrick), layerType, boardX, boardY, bLeft)
		, mbRed(bRed)
	{
	}

	void Brick::Update()
	{
	}
}