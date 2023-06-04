#include "Object.h"
#include "RenderManager.h"
#include "Sprite.h"

namespace catInWonderland
{
	Object::Object(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eObjectType objectType, eLayerType layerType, bool bLeft)
		: mWorldRectangle(worldRectangle)
		, mSpriteRectangle(spriteRectangle)
		, mSpriteType(spriteType)
		, mObjectType(objectType)
		, mbLeft(bLeft)
		, mLayerType(layerType)
	{
	}

	Object::Object(const ObjectInfo& objectInfo)
		: Object(objectInfo.WorldRectangle,
			objectInfo.SpriteRectangle,
			objectInfo.Sprite,
			objectInfo.ObjectType,
			objectInfo.LayerType,
			objectInfo.bLeft)
	{
	}

	void Object::SetIsLeft(bool bLeft)
	{
		mbLeft = bLeft;
	}
}