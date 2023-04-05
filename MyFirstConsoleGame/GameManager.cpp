#pragma once

#include <Windows.h>

namespace hongpireSurvivors
{
	class GameManaer
	{
	public:
		static GameManaer* GetInstance();
		static void DeleteInstance();

		void Frame();

	private:
		GameManaer();
		~GameManaer() = default;

	private:
		static GameManaer* mInstance;

		COORD mCamaraPos;
		
	};
}