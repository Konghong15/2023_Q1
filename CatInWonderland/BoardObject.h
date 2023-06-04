#pragma once

#include "Object.h"

namespace catInWonderland
{
	class BoardObject : public Object
	{
	public:
		BoardObject(const ObjectInfo& objectInfo, size_t boardX, size_t boardY);
		BoardObject(hRectangle worldRectangle, hRectangle spriteRectangle, eSpriteType spriteType, eObjectType objectType, eLayerType layerType, size_t boardX, size_t boardY, bool bLeft = true);
		virtual ~BoardObject() = default;

		virtual void Update(float deltaTime) = 0;

		virtual void RotateBoardIndex(bool bLeft);
		void Rotate(float originX, float originY, float cosf, float sinf);
		void Rotate(float originX, float originY, float radian);
		void AlignWorldRectagle();

		inline void MoveInBoard(int boardX, int boardY);
		inline void SetBoardIndex(unsigned int boardX, unsigned int boardY);

		inline size_t GetBoardX() const;
		inline size_t GetBoardY() const;
		inline bool CompareBoardIndex(const BoardObject& boardObject) const;
		inline bool CompareBoardIndex(int boardX, int boardY) const;

	protected:
		size_t mBoardX;
		size_t mBoardY;
	};

	void BoardObject::MoveInBoard(int boardX, int boardY)
	{
		mBoardX += boardX;
		mBoardY += boardY;
	}

	void BoardObject::SetBoardIndex(unsigned int boardX, unsigned int boardY)
	{
		mBoardX = boardX;
		mBoardY = boardY;
	}

	size_t BoardObject::GetBoardX() const
	{
		return mBoardX;
	}

	size_t BoardObject::GetBoardY() const
	{
		return mBoardY;
	}

	bool BoardObject::CompareBoardIndex(const BoardObject& boardObject) const
	{
		return mBoardX == boardObject.mBoardX && mBoardY == boardObject.mBoardY;
	}

	bool BoardObject::CompareBoardIndex(int boardX, int boardY) const
	{
		return mBoardX == boardX && mBoardY == boardY;
	}
}