#pragma once

#include "hRectangle.h"
#include "eObjectType.h"
#include "eAnimaitonType.h"
#include "eSpriteType.h"
#include "eLayerType.h"

namespace catInWonderland
{
	struct ObjectInfo
	{
		hRectangle WorldRectangle;
		hRectangle SpriteRectangle;
		eSpriteType Sprite;
		eObjectType ObjectType;
		eLayerType LayerType;
		bool bLeft;
	};
}