#include "Object.h"
#include "RenderManager.h"
#include "SceneManager.h"
#include "Collider.h"

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
}