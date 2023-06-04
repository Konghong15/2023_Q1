#pragma once

#include <cassert>
#include <vector>

#include "hRectangle.h"

namespace catInWonderland
{
	class BoardManager final
	{
	public:
		BoardManager();
		~BoardManager() = default;
		BoardManager(const BoardManager&) = delete;
		BoardManager operator=(const BoardManager&) = delete;

		void CreateBoard(size_t boardSize, size_t boardPadding, size_t cellPadding);

		inline void AlignRectangle(size_t indexX, size_t indexY, hRectangle* outRectangle) const;
		inline void RotateRight(size_t* outIndexX, size_t* outIndexY) const;
		inline void RotateLeft(size_t* outIndexX, size_t* outIndexY) const;

		inline float GetCellSize() const;
		inline size_t GetBoardSize() const;
		inline const hRectangle& GetWorldRectangle(size_t objectX, size_t ObjectY) const;

	private:
		enum { RESERVE_SIZE = 128 };

		size_t mBoardSize;
		size_t mBoardPadding;
		size_t mCellPadding;
		std::vector<hRectangle> mWorldRectangles;
	};

	void BoardManager::AlignRectangle(size_t indexX, size_t indexY, hRectangle* outRectangle) const
	{
		const hRectangle& alignedRectangle = GetWorldRectangle(indexX, indexY);
		*outRectangle = alignedRectangle;
	}

	void BoardManager::RotateRight(size_t* outIndexX, size_t* outIndexY) const
	{
		assert(outIndexX != nullptr && outIndexY != nullptr);
		assert(*outIndexX < mBoardSize && (*outIndexY) < mBoardSize);

		size_t y = *outIndexY;
		*outIndexY = *outIndexX;
		*outIndexX = mBoardSize - 1 - y;
	}

	void BoardManager::RotateLeft(size_t* outIndexX, size_t* outIndexY) const
	{
		assert(outIndexX != nullptr && outIndexY != nullptr);
		assert(*outIndexX < mBoardSize && (*outIndexY) < mBoardSize);

		size_t x = *outIndexX;
		*outIndexX = *outIndexY;
		*outIndexY = mBoardSize - 1 - x;
	}

	float BoardManager::GetCellSize() const
	{
		assert(!mWorldRectangles.empty());

		return mWorldRectangles.at(0).GetWidth();
	}

	size_t BoardManager::GetBoardSize() const
	{
		return mBoardSize;
	}

	const hRectangle& BoardManager::GetWorldRectangle(size_t objectX, size_t objectY) const
	{
		assert(objectX < mBoardSize || objectY < mBoardSize);

		return mWorldRectangles.at(objectX + objectY * mBoardSize);
	}
}