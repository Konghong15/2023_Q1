#include "Object.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Collider.h"
#include "WinApp.h"

namespace hockman
{
	Object::Object(hRectangle rectangle, eSpriteType spriteType, eObjectType objectType)
		: mRectangle(rectangle)
		, mSpriteType(spriteType)
		, mObjectType(objectType)
		, mIsVaild(true)
		, mCollider(nullptr)
	{
	}

	Object::~Object()
	{
		delete mCollider;
		mCollider = nullptr;
	}

	void Object::AddCollider(Collider* collider)
	{
		if (mCollider == nullptr)
		{
			mCollider = collider;
		}
	}

	void Object::Render()
	{
		RenderManager::GetInstance()->DrawRect(mRectangle, RGB(0, 0, 0));
	}


	void Object::Rotate(float radian)
	{
		Vector2 topLeft = mRectangle.GetTopLeft();
		Vector2 bottomRight = mRectangle.GetBottomRight();

		const size_t CETNER_X = WinApp::GetWidth() / 2;
		const size_t CENTER_Y = WinApp::GetHeight() / 2;

		topLeft.SetX(pos.GetX() - CETNER_X);
		topLeft.SetY(pos.GetY() - CENTER_Y);
		// È¸Àü
		{
			float cosScalr = cos(radian);
			float sinScalr = sin(radian);
			Vector2 temp;

			temp.SetX(pos.GetX() * cosScalr - pos.GetY() * sinScalr);
			temp.SetY(pos.GetX() * sinScalr + pos.GetY() * cosScalr);
			pos = temp;
		}
		pos.SetX(pos.GetX() + CETNER_X);
		pos.SetY(pos.GetY() + CENTER_Y);

		mRectangle.SetPos(pos);

		const size_t WIDTH = mRectangle.GetSize().GetX();
		const size_t HEIGHT = mRectangle.GetSize().GetY();
		mRectangle.Setsize(HEIGHT, WIDTH);
	}
}