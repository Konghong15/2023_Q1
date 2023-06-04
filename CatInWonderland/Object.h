#pragma once

#include "ObjectInfo.h"
#include "eLayerType.h"
#include "eAnimaitonType.h"
#include "eSpriteType.h"

namespace catInWonderland
{
	class Sprtie;

	class Object
	{
	public:
		Object(const ObjectInfo& objectInfo);
		Object(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eObjectType objectType, eLayerType layerType, bool bLeft = true);
		virtual ~Object() = default;

		virtual void Update(float deltaTime) = 0;

		inline void MoveInWorld(float x, float y);
		virtual void SetIsLeft(bool bLeft);

		inline void SetSpriteType(eSpriteType spriteType);
		inline void SetSpriteRectangle(const hRectangle& spriteRectangle);
		inline void SetLayerType(eLayerType layerType);
		inline void SetWorldRectangle(const hRectangle& spriteRectangle);
		inline void SetVisible(bool bVisible);

		inline bool GetIsLeft() const;
		inline const hRectangle& GetWorldRectangle() const;
		inline eObjectType GetObjectType() const;
		inline eLayerType GetLayerType() const;
		inline eSpriteType GetSpriteType() const;
		inline bool GetIsVisible() const;

	protected:
		hRectangle mWorldRectangle;
		hRectangle mSpriteRectangle;
		eLayerType mLayerType;
		eSpriteType mSpriteType;
		eObjectType mObjectType;
		bool mbLeft;
		bool mbVisible;
	};

	void Object::SetSpriteType(eSpriteType spriteType)
	{
		mSpriteType = spriteType;
	}

	void Object::SetSpriteRectangle(const hRectangle& spriteRectangle)
	{
		mSpriteRectangle = spriteRectangle;
	}

	void Object::SetWorldRectangle(const hRectangle& worldRectangle)
	{
		mWorldRectangle = worldRectangle;
	}

	void Object::SetVisible(bool bVisible)
	{
		mbVisible = bVisible;
	}

	bool Object::GetIsVisible() const
	{
		return mbVisible;
	}

	bool Object::GetIsLeft() const
	{
		return mbLeft;
	}

	const hRectangle& Object::GetWorldRectangle() const
	{
		return mWorldRectangle;
	}

	eObjectType Object::GetObjectType() const
	{
		return mObjectType;
	}

	eSpriteType Object::GetSpriteType() const
	{
		return mSpriteType;
	}

	void Object::MoveInWorld(float x, float y)
	{
		mWorldRectangle.Move(x, y);
	}

	eLayerType Object::GetLayerType() const
	{
		return mLayerType;
	}

	void Object::SetLayerType(eLayerType layerType)
	{
		mLayerType = layerType;
	}
}