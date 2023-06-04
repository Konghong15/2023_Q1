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

	class InputManager final
	{
	public:
		InputManager();
		~InputManager() = default;
		InputManager(const InputManager&) = delete;
		InputManager operator=(const InputManager&) = delete;

		void Init();
		void Update();

		inline eKeyState GetKeyState(WORD keyCode);
		inline const POINT& GetMousePos() const;

	private:
		enum { KEY_SIZE = 255 };

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