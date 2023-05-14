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

		// ���� �̵�(��ũ�� -> ȭ�� �߾�)
		topLeft.SetX(topLeft.GetX() - CETNER_X);
		topLeft.SetY(topLeft.GetY() - CENTER_Y);
		bottomRight.SetX(bottomRight.GetX() - CETNER_X);
		bottomRight.SetY(bottomRight.GetY() - CENTER_Y);

		// ȸ��
		{
			float cosScalr = cos(radian);
			float sinScalr = sin(radian);
			Vector2 temp;

			temp.SetX(topLeft.GetX() * cosScalr - topLeft.GetY() * sinScalr);
			temp.SetY(topLeft.GetX() * sinScalr + topLeft.GetY() * cosScalr);
			topLeft = temp;

			temp.SetX(bottomRight.GetX() * cosScalr - bottomRight.GetY() * sinScalr);
			temp.SetY(bottomRight.GetX() * sinScalr + bottomRight.GetY() * cosScalr);
			bottomRight = temp;
		}

		// ���� �̵�(ȭ�� �߾� -> ��ũ��)
		topLeft.SetX(topLeft.GetX() + CETNER_X);
		topLeft.SetY(topLeft.GetY() + CENTER_Y);
		bottomRight.SetX(bottomRight.GetX() + CETNER_X);
		bottomRight.SetY(bottomRight.GetY() + CENTER_Y);

		mRectangle = hRectangle(topLeft, bottomRight);
	}
}