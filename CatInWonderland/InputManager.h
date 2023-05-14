#pragma once

#include <Windows.h>

namespace catInWonderland
{
	enum class eKeyState
	{
		NONE,
		PUSH,
		HOLD,
		POP
	};

	class InputManager
	{
	public:
		static InputManager* GetInstance();
		static void DeleteInstance();

		void Reset();
		void Frame();

		inline eKeyState GetKeyState(WORD keyCode);
		inline const POINT& GetMousePos() const;

	private:
		InputManager() = default;
		~InputManager() = default;

	private:
		enum { KEY_SIZE = 255 };
		static InputManager* mInstance;

		POINT mMousePos;
		eKeyState mKeyState[KEY_SIZE];
	};

	eKeyState InputManager::GetKeyState(WORD keyCode)
	{
		return mKeyState[keyCode];
	}

	const POINT& InputManager::GetMousePos() const
	{
		return mMousePos;
	}
}