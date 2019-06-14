#include <Windows.h>
#include <random>
#include <time.h>
#include <math.h>

#include "Location.h"
#include "Omok.h"

const wchar_t CLASSNAME[] = L"Omok";
const wchar_t WINDOWNAME[] = L"Omok";

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 960;

Location beforeMouse(0, 0);
Location nowMouse(0, 0);
bool mouseDown = false;

//double buffering

HDC board;
HBITMAP bitmap;
HWND winHandle;
HDC winCon;
HINSTANCE instance;

//by messageBox
void PrintError(const wchar_t* err)
{
	MessageBox(winHandle, err, L"ERROR", MB_OK);
}

LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		winCon = GetDC(hwnd);
		board = CreateCompatibleDC(winCon);
		bitmap = CreateCompatibleBitmap(winCon, WINDOW_WIDTH, WINDOW_HEIGHT);
		SelectObject(board, bitmap);
		BitBlt(board, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, 0, 0, WHITENESS);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		ps.fErase = 1;
		BeginPaint(winHandle, &ps);

		//

		BitBlt(ps.hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, board, 0, 0, SRCCOPY);
		EndPaint(winHandle, &ps);
		return 0;
	case WM_LBUTTONDOWN:
		mouseDown = true;
		return 0;
	case WM_LBUTTONUP:
		mouseDown = false;
		return 0;
	case WM_DESTROY:
		DeleteDC(board);
		DeleteObject(bitmap);
		ReleaseDC(hwnd, winCon);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	WNDCLASSEX winc;
	winc.cbSize = sizeof(winc);
	winc.style = 0;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hInstance = hInstance;
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.cbClsExtra = 0;
	winc.cbWndExtra = 0;
	winc.hbrBackground = NULL;
	winc.lpszMenuName = WINDOWNAME;
	winc.lpszClassName = CLASSNAME;
	winc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winc.lpfnWndProc = winProc;
	if (!(RegisterClassEx(&winc)))
	{
		PrintError(L"Cannot register class");
		return 0;
	}
	instance = hInstance;
	winHandle = CreateWindowEx(NULL, CLASSNAME, WINDOWNAME, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);
	ShowWindow(winHandle, CmdShow);
	UpdateWindow(winHandle);

	MSG msg;
	long time, time2;
	time = clock();

	bool b = false, changed = false;
	while (1)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				PostQuitMessage(0);
				goto QUIT;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		if ((time2 = clock()) - time < 1000 / 1000)
			continue;
		InvalidateRect(winHandle, NULL, true);
	}
QUIT:
	UnregisterClass(CLASSNAME, hInstance);
	return 0;
}