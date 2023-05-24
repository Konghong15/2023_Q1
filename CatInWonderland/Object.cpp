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

	void Object::Rotate(int originX, int originY, float radian)
	{
		mRectangle.Rotate(originX, originY, radian);
	}

	void Object::RotateIndex(bool bLeft)
	{
		if (bLeft)
		{
			BoardManager::GetInstance()->RotateLeft(&mIndexX, &mIndexY);
		}
		else
		{
			BoardManager::GetInstance()->RotateRight(&mIndexX, &mIndexY);
		}

		const hRectangle& alignedRectangle = BoardManager::GetInstance()->GetWorldRect(mIndexX, mIndexY);
		const float MAX_DISTANCE = alignedRectangle.GetHeight() < alignedRectangle.GetWidth() ? alignedRectangle.GetHeight() * 0.5f : alignedRectangle.GetWidth() * 0.5f;

		for (size_t i = 0; i < static_cast<size_t>(eRectangleIndex::Size); ++i)
		{
			eRectangleIndex iType = static_cast<eRectangleIndex>(i);
			const Vector2& iVertex = mRectangle.GetVertex(iType);

			for (size_t j = 0; j < static_cast<size_t>(eRectangleIndex::Size); ++j)
			{
				eRectangleIndex jTpye = static_cast<eRectangleIndex>(j);
				const Vector2& jVertex = alignedRectangle.GetVertex(jTpye);

				if (Vector2::GetDistance(iVertex, jVertex) < MAX_DISTANCE)
				{
					mRectangle.SetVertex(iType, jVertex);
					break;
				}
			}
		}
	}

	void Object::adjustRectangle()
	{

	}
}