#pragma once

#include "eObjectType.h"
#include "eSpriteType.h"
#include "Vector2.h"

namespace hockman
{
	class Collider;
	class Scene;

	class Object
	{
	public:
		Object(Vector2 pos, Vector2 size, Vector2 direction, eSpriteType spriteType, eObjectType objectType);
		virtual ~Object();

		virtual void Frame() = 0;
		virtual void Render();

		void AddCollider(Collider* collider);

		//inline const COORD& GetPos() const;
		//inline const COORD& GetSize() const;
		//inline const eSpriteType& GetSpriteType() const;
		//inline const eObjectType& GetObjectType() const;
		//inline bool GetValid() const;
		//inline bool GetIsLeft() const;

	protected:
		Vector2 mPos;
		Vector2 mSize;
		Vector2 mDirection;
		eSpriteType mSpriteType;
		eObjectType mObjectType;
		Collider* mCollider;
		bool mIsVaild;
	};
}