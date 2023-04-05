#include "Object.h"
#include "RenderManager.h"

namespace hongpireSurvivors
{
	Object::Object(COORD pos, COORD size, eSpriteType spriteType, eObjectType objectType, bool isValid)
		: mPos(pos)
		, mSize(size)
		, mSpriteType(spriteType)
		, mObjectType(objectType)
		, mIsVaild(isValid)
		, mCollider(nullptr)
	{
	}

	Object::~Object()
	{
		delete mCollider;
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
		RenderManager::GetInstance()->Draw(mPos.X, mPos.Y, mSpriteType);
	}
}