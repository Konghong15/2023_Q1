#include "Object.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "BoardManager.h"
#include "WinApp.h"

namespace catInWonderland
{
	Object::Object(hRectangle rectangle, size_t indexX, size_t indexY)
		: mRectangle(rectangle)
		, mIndexX(indexX)
		, mIndexY(indexY)
		, mIsVaild(true)
	{
	}

	Object::~Object()
	{
	}

	void Object::Render()
	{
		RenderManager::GetInstance()->DrawRect(mRectangle, RGB(255, 0, 0));
	}

	void Object::Move(float distanceX, float distanceY)
	{
		const Vector2& pos = mRectangle.GetTopLeft();
		mRectangle.SetPos(pos.GetX() + distanceX, pos.GetY() + distanceY);
	}

	void Object::Rotate(bool bLeft)
	{
		if (bLeft)
		{
			BoardManager::GetInstance()->RotateLeft(&mIndexX, &mIndexY);
		}
		else
		{
			BoardManager::GetInstance()->RotateRight(&mIndexX, &mIndexY);
		}

		mRectangle = BoardManager::GetInstance()->GetWorldRect(mIndexX, mIndexY);
	}
}