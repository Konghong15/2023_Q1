#include <cassert>

#include "Creator.h"
#include "BoardManager.h"
#include "Player.h"
#include "Brick.h"
#include "Butterfly.h"
#include "SpriteManager.h"
#include "ConstantTable.h"
#include "Obstacle.h"
#include "ChangeColorTile.h"
#include "Portal.h"
#include "eLayerType.h"

namespace catInWonderland
{
	BoardObject* Creator::CreateBoardObject(const BoardObjectInfo& boardObjectInfo)
	{
		hRectangle worldRect = BoardManager::GetInstance()->GetWorldRectangle(boardObjectInfo.BoardX, boardObjectInfo.BoardY);

		switch (boardObjectInfo.ObjectType)
		{
		case eObjectType::Player:
			return new Player(worldRect, SpriteManager::GetInstance()->GetSpriteRectangle(eAnimationType::PlayerIdle, 0), &SpriteManager::GetInstance()->GetSprite(eSpriteType::Player), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY);
		case eObjectType::RedBrick:
			return new Brick(worldRect, BRICK_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::RedBrick), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, true);
		case eObjectType::BlueBrick:
			return new Brick(worldRect, BRICK_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::BlueBrick), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, false);
		case eObjectType::Obstacle:
			return new Obstacle(worldRect, OBSTACLE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::Obstacle), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, true);
		case eObjectType::BlueChangeColorTile:
			return new ChangeColorTile(worldRect, TITLE_CHANGECOLORTILE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::BlueChangeColorTile), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, false);
		case eObjectType::RedChangeColorTile:
			return new ChangeColorTile(worldRect, TITLE_CHANGECOLORTILE_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::RedChangeColorTile), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, true);
		case eObjectType::YellowPortal:
			return new Portal(worldRect, PORTAL_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::YellowPortal), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, true);
		case eObjectType::PurplePortal:
			return new Portal(worldRect, PORTAL_RECT, &SpriteManager::GetInstance()->GetSprite(eSpriteType::PurplePortal), eLayerType::NonBlendObject, boardObjectInfo.BoardX, boardObjectInfo.BoardY, true);
		default:
			assert(false);
			break;
		}

		return nullptr;
	}
}
