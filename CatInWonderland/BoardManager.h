#pragma once

#include <cassert>
#include <vector>

#include "hRectangle.h"

namespace catInWonderland
{
	class BoardManager
	{
	public:
		static BoardManager* GetInstance();
		static void DeleteInstance();

		void RotateRight(size_t* outIndexX, size_t* outIndexY);
		void RotateLeft(size_t* outIndexX, size_t* outIndexY);

		inline size_t GetBoardSize() const;
		inline const hRectangle& GetWorldRect(size_t objectX, size_t ObjectY);

		void SetBoardSize(size_t size);

	private:
		BoardManager() = default;
		~BoardManager() = default;

		void init();
		void release();

	private:
		enum { MAX_BOARD_SIZE = 10 };
		enum { BOARD_PADDING = 200 };
		enum { CELL_PADDING = 5 };

		static BoardManager* mInstance;

		size_t mBoardSize;
		std::vector<hRectangle> mWorldRectangles;
	};

	size_t BoardManager::GetBoardSize() const
	{
		return mBoardSize;
	}

	const hRectangle& BoardManager::GetWorldRect(size_t objectX, size_t objectY)
	{
		assert(objectX < mBoardSize || objectY < mBoardSize);

		return mWorldRectangles.at(objectX + objectY * mBoardSize);
	}
}