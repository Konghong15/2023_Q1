#pragma once

#include "BoardObjectInfo.h"

namespace catInWonderland
{
	class BoardObject;

	class Creator
	{
	public:
		static BoardObject* CreateBoardObject(const BoardObjectInfo& boardObjectInfo);
	};
}