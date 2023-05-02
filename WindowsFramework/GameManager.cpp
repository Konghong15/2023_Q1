#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <assert.h>

#include "WinApp.h"
#include "InputSystem.h"
#include "TimeSystem.h"
#include "RenderSystem.h"

#include "GameManager.h"

#include <string>

#pragma comment(lib, "User32.lib")

#pragma comment(lib, "Msimg32.lib")
namespace game
{
	struct Object
	{
		float x;
		float y;
		float size;
		float speed;

		COLORREF color;

		void SetPos(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void Move(float x, float y)
		{
			this->x += x;
			this->y += y;
		}
	};

	Object player = { global::GetWinApp().GetWidth() / 2 ,global::GetWinApp().GetHeight() / 2, 10, 10, RGB(255, 255, 0) };
	POINT playerWidth = { 20, 20 };
	float fAngleInRadian = 0.f;
	HDC textureDC;

	const int bludeCircleMax = 100;
	int blueCircleCount = 0;
	Object blueCircles[bludeCircleMax];


	void UpdatePlayer()
	{
		if (input::IsKeyDown('A'))
		{
			player.Move(-player.speed, 0);
		}
		else if (input::IsKeyDown('D'))
		{
			player.Move(player.speed, 0);
		}
		if (input::IsKeyDown('W'))
		{
			player.Move(0, -player.speed);
		}
		else if (input::IsKeyDown('S'))
		{
			player.Move(0, player.speed);
		}

		if (input::IsKeyDown(VK_LEFT))
		{
			fAngleInRadian += 0.01f;
		}
		else if (input::IsKeyDown(VK_RIGHT))
		{
			fAngleInRadian -= 0.01f;
		}
	}

	void UpdateBlueCircle()
	{
		const input::MouseState& mouse = input::GetMouseState();
		const input::MouseState& prevmouse = input::GetPrevMouseState();

		if (input::IsSame(mouse, prevmouse))
		{
			return;
		}

		if (blueCircleCount < bludeCircleMax && mouse.left)
		{
			blueCircles[blueCircleCount].SetPos(mouse.x, mouse.y);
			blueCircles[blueCircleCount].color = RGB(0, 0, 255);
			blueCircles[blueCircleCount].size = 10;
			blueCircles[blueCircleCount].speed = 0;
			blueCircleCount++;
		}
	}

	GameManager* GameManager::instance = nullptr;
	GameManager::GameManager()
	{
	}
	GameManager::~GameManager()
	{
	}

	void GameManager::Initialize()
	{
		_CrtDumpMemoryLeaks();

		const TCHAR* path = TEXT("img.bmp");

		HBITMAP Bm_hBit = (HBITMAP)LoadImage(nullptr, path, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
		_CrtDumpMemoryLeaks();

		input::InitInput();
		time::InitTime();
		render::InitRender();

		int error = GetLastError();
		assert(Bm_hBit != nullptr);

		// 비트맵과 연결할 DC
		// 이거 역할이 뭐야?
		textureDC = CreateCompatibleDC(render::frontMemDC);

		//GetPixel()
		//HBITMAP hPrevBit = (HBITMAP)SelectObject(textureDC, Bm_hBit);
		//DeleteObject(hPrevBit);

		// 비트맵 정보
	}

	void GameManager::Update()
	{
		++m_UpdateCount;

		input::UpdateMouse();

		time::UpdateTime();

		UpdatePlayer();
		UpdateBlueCircle();

		input::ResetInput();

	}

	void GameManager::FixeUpdate()
	{
		static ULONGLONG elapsedTime;

		elapsedTime += time::GetDeltaTime();

		while (elapsedTime >= 20) //0.02초
		{
			++m_FixedUpdateCount;

			elapsedTime -= 20;
		}
	}

	void GameManager::Render()
	{
		render::BeginDraw();

		DrawFPS();
		DrawSomething();
		DrawPlayer();

		render::EndDraw();
	}
	void GameManager::Finalize()
	{
		render::ReleaseRender();
	}
	void GameManager::Run()
	{
		MSG msg;

		while (true)
		{
			if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT) break;

				if (msg.message == WM_KEYDOWN)
				{
					input::KeyDown(msg.wParam);
				}
				else if (msg.message == WM_KEYUP)
				{
					input::KeyUp(msg.wParam);
				}
				else
				{
					DispatchMessage(&msg);
				}
			}
			else
			{
				FixeUpdate();

				Update();

				Render();
			}
		}
	}

	GameManager* GameManager::GetInstance()
	{
		if (instance == nullptr)
		{
			instance = new GameManager();
		}
		return instance;
	}
	void GameManager::DestroyInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}

	void GameManager::DrawFPS()
	{
		static ULONGLONG elapsedTime;
		static int UpdateCount;
		static int FixedUpdateCount;

		elapsedTime += time::GetDeltaTime();

		if (elapsedTime >= 1000)
		{
			elapsedTime = 0;
			;
			UpdateCount = m_UpdateCount;
			FixedUpdateCount = m_FixedUpdateCount;

			m_UpdateCount = 0;
			m_FixedUpdateCount = 0;
		}

		float frameRate = time::GetFrameRate();
		std::string str = "FPS: " + std::to_string(frameRate);
		str += "           Update " + std::to_string(UpdateCount);
		str += "           FixedUpdate " + std::to_string(FixedUpdateCount);

		render::DrawText(10, 10, str.c_str(), RGB(255, 0, 0));

	}

	void GameManager::DrawPlayer()
	{
		enum { PLAYER_WIDTH = 100 };
		enum { PLAYER_HEIGHT = 100 };
		render::DrawCircle(player.x, player.y, player.size, player.color);
		render::DrawRotatineRect(player.x - PLAYER_WIDTH / 2, player.y - PLAYER_HEIGHT / 2, PLAYER_WIDTH, PLAYER_HEIGHT, fAngleInRadian, textureDC);
		// void DrawRotatineRect(int x, int y, int w, int h, float angleInRadian, HDC textureDC)
	}

	void GameManager::DrawSomething()
	{

		for (int i = 0; i < blueCircleCount; i++)
		{
			render::DrawCircle(blueCircles[i].x, blueCircles[i].y, blueCircles[i].size, blueCircles[i].color);
		}

		render::DrawLine(player.x - 50, player.y + 50, player.x + 50, player.y + 50, RGB(255, 0, 0));
		render::DrawRect(player.x - 25, player.y - 25, 50, 50, RGB(255, 0, 255));

	}
}