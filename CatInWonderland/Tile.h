#pragma once
#include "BoardObject.h"

namespace catInWonderland	//배경 그리기
{
	class Tile : public BoardObject
	{
	public:
		Tile(const ObjectInfo& objectInfo, size_t boardX, size_t boardY);
		Tile(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft = true);
		virtual ~Tile() = default;

		virtual void Update(float deltaTime) override;
	};
}