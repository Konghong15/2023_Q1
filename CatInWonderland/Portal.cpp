#include "Portal.h"

namespace catInWonderland
{
	Portal::Portal(const ObjectInfo& objectInfo, size_t boardX, size_t boardY, bool bPortalColor)
		: BoardObject(objectInfo, boardX, boardY)
		, mbPortalColor(bPortalColor)
	{
	}

	Portal::Portal(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eLayerType layerType, size_t boardX, size_t boardY, bool bPortalColor, bool bLeft)
		: BoardObject(worldRectangle, spriteRectangle, sprite, (mbPortalColor ? eObjectType::YellowPortal : eObjectType::PurplePortal), layerType, boardX, boardY, bLeft)
		, mbPortalColor(bPortalColor)
	{
	}

	void Portal::Update()
	{
		assert(mConnectedPortal != nullptr);
	}
}