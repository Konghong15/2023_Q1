#include "Object.h"
#include "RenderManager.h"
#include "ObjectManager.h"
#include "Scene.h"
#include "SceneManager.h"

namespace hongpireSurvivors
{
	// Frmae time based on 30FPS
	const float Object::ONE_FRAME_TIME = 0.033f;

	Object::Object(COORD pos, COORD size, eSpriteType spriteType, eObjectType objectType, bool isLeft)
		: mPos(pos)
		, mSize(size)
		, mSpriteType(spriteType)
		, mObjectType(objectType)
		, mIsVaild(true)
		, mCollider(nullptr)
		, mIsLeft(isLeft)
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
		int x = mPos.X - SceneManager::GetInstance()->GetCurScene()->GetCamaraPos().X;

		if (x >= 0 && x + mSize.X < 400)
		{
			RenderManager::GetInstance()->Draw(x, mPos.Y, mSpriteType, mIsLeft);
		}
	}
}