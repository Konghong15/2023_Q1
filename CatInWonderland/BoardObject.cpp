#include <cassert>

#include "InputManager.h"
#include "BoardManager.h"
#include "WinApp.h"
#include "BoardObject.h"

namespace catInWonderland
{
	BoardObject::BoardObject(const ObjectInfo& objectInfo, size_t boardX, size_t boardY)
		: Object(objectInfo)
		, mBoardX(boardX)
		, mBoardY(boardY)
	{
	}

	BoardObject::BoardObject(hRectangle worldRectangle, hRectangle spriteRectangle, Sprite* sprite, eObjectType objectType, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft)
		: Object(worldRectangle, spriteRectangle, sprite, objectType, layerType, bLeft)
		, mBoardX(boardX)
		, mBoardY(boardY)
	{
	}

	void BoardObject::Rotate(float originX, float originY, float cosf, float sinf)
	{
		mWorldRectangle.Rotate(originX, originY, cosf, sinf);
	}

	void BoardObject::Rotate(float originX, float originY, float radian)
	{
		mWorldRectangle.Rotate(originX, originY, radian);
	}

	void BoardObject::RotateBoardIndex(bool bLeft)
	{
		if (bLeft)
		{
			BoardManager::GetInstance()->RotateLeft(&mBoardX, &mBoardY);
		}
		else
		{
			BoardManager::GetInstance()->RotateRight(&mBoardX, &mBoardY);
		}
	}

	void BoardObject::AlignWorldRectagle()
	{
		BoardManager::GetInstance()->AlignRectangle(mBoardX, mBoardY, &mWorldRectangle);
	}
}