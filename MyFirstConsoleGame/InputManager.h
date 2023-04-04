#pragma once

namespace hongpireSurvivors
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

		void Frame();
		inline eKeyState GetKeyState(WORD keyCode);

	private:
		InputManager();
		~InputManager() = default;

	private:
		enum { KEY_SIZE = 255 };
		static InputManager* mInstance;

		eKeyState mKeyState[KEY_SIZE];
	};

	eKeyState InputManager::GetKeyState(WORD keyCode)
	{
		return mKeyState[keyCode];
	}
}