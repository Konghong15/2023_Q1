#include <cmath>

#include "WinApp.h"
#include "RenderSystem.h"

#pragma comment(lib, "msimg32.lib")

namespace render
{
	HWND hWnd;

	HDC frontMemDC;	// �ո� DC
	HDC backMemDC;	// �޸� DC

	HBITMAP backBitmap = nullptr;

	void InitRender()
	{
		hWnd = global::GetWinApp().GetWindow();

		frontMemDC = GetDC(hWnd);

		backMemDC = CreateCompatibleDC(frontMemDC);

		backBitmap = CreateCompatibleBitmap(frontMemDC, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight());
	}

	void ClearScreen()
	{
		::PatBlt(backMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), WHITENESS);
	}

	void BeginDraw()
	{
		ClearScreen();

		::SelectObject(backMemDC, backBitmap);
	}

	void EndDraw()
	{
		::BitBlt(frontMemDC, 0, 0, global::GetWinApp().GetWidth(), global::GetWinApp().GetHeight(), backMemDC, 0, 0, SRCCOPY);
	}

	void ReleaseRender()
	{
		DeleteObject(backBitmap);

		DeleteDC(backMemDC);

		ReleaseDC(hWnd, frontMemDC);
	}

	void DrawLine(int x1, int y1, int x2, int y2, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 5, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		MoveToEx(backMemDC, x1, y1, NULL);

		LineTo(backMemDC, x2, y2);

		SelectObject(backMemDC, hOldPen);

		DeleteObject(hPen);
	}


	void DrawRect(int x, int y, int width, int height, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		hRectangle(backMemDC, x, y, x + width, y + height);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

void DrawRotatineRect(int x, int y, int w, int h, float angleInRadian, HDC textureDC)
{
	POINT points[3] = { 0, };

	points[0] = { x, y };
	points[1] = { x + w, y };
	points[2] = { x, y + h };

	// ������Ʈ ���� ��ǥ�� �����̵�
	POINT center = { x + w / 2, y + h / 2 };
	{
		for (int i = 0; i < 3; ++i)
		{
			points[i].x -= center.x;
			points[i].y -= center.y;
		}
	}

	// ȸ��
	{
		float cosScalr = cos(angleInRadian);
		float sinScalr = sin(angleInRadian);
		POINT temp;

		for (int i = 0; i < 3; ++i)
		{
			temp.x = points[i].x * cosScalr - points[i].y * sinScalr;
			temp.y = points[i].x * sinScalr + points[i].y * cosScalr;
			points[i] = temp;
		}
	}

	// ���� ��ǥ�� �����̵�
	{
		for (int i = 0; i < 3; ++i)
		{
			points[i].x += center.x;
			points[i].y += center.y;
		}
	}

	// UV��ǥ ����
	POINT UV = { 37, 40 };
	POINT UV_SIZE = { 21, 24 };
	PlgBlt(backMemDC, points, textureDC, UV.x, UV.y, UV_SIZE.x, UV_SIZE.y, 0, 0, 0);
}

	void DrawCircle(int x, int y, int radius, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		Ellipse(backMemDC, x - radius, y - radius, x + radius, y + radius);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);
	}

	void DrawPolygon(POINT points[], int count, COLORREF color)
	{
		HPEN hPen = CreatePen(PS_SOLID, 1, color);

		HPEN hOldPen = (HPEN)SelectObject(backMemDC, hPen);

		HBRUSH hBrush = CreateSolidBrush(color);

		HBRUSH hOldBrush = (HBRUSH)SelectObject(backMemDC, hBrush);

		Polygon(backMemDC, points, count);

		SelectObject(backMemDC, hOldPen);
		SelectObject(backMemDC, hOldBrush);

		DeleteObject(hPen);
		DeleteObject(hBrush);

	}

	void DrawText(int x, int y, const char* text, COLORREF color)
	{
		SetTextColor(backMemDC, color);

		TextOutA(backMemDC, x, y, text, strlen(text));
	}

}