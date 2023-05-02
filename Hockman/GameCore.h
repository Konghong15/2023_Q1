#pragma once

namespace hockman
{
	class GameCore
	{
	public:
		static GameCore* GetInstance();
		static void DeletInstance();

		void Init();
		void Frame();
		void Release();

	private:
		GameCore() = default;
		~GameCore() = default;

	private:
		static GameCore* mInstance;
	};
}