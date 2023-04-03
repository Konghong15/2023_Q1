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
		InputManager();
		~InputManager() = default;

		static InputManager* GetInstance();
		static void DeleteInstance();

		void Frame();

	private:
		enum { KEY_SIZE = 255 };
		static InputManager* mInstance;

		eKeyState mkeyState[KEY_SIZE];
	};
}