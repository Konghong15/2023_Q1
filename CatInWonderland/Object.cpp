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
		mRectangle.Move(distanceX, distanceY);
	}

	void Object::Rotate(float radian, int originX, int originY)
	{
		mRectangle.Rotate(Vector2(originX, originY), radian);
	}
}