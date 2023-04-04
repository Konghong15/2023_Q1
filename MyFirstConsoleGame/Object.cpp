#include "Object.h"
#include "RenderManager.h"

namespace hongpireSurvivors
{
	Object::Object(COORD pos, COORD size, eSpriteType spriteType)
		: mPos(pos)
		, mSize(size)
		, mSpriteType(spriteType)
	{
	}

	void Object::Render()
	{
		RenderManager::GetInstance()->Draw(mPos.X, mPos.Y, mSpriteType);
	}
}