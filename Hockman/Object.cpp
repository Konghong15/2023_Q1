#include "Object.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Collider.h"

namespace hockman
{
	Object::Object(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, eObjectType objectType)
		: mPos(pos)
		, mSize(size)
		, mDirection(direction)
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
	}
}