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

//double buffering

HDC buffer;
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
		buffer = CreateCompatibleDC(winCon);
		bitmap = CreateCompatibleBitmap(winCon, WINDOW_WIDTH, WINDOW_HEIGHT);
		SelectObject(buffer, bitmap);
		BitBlt(buffer, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, 0, 0, WHITENESS);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(winHandle, &ps);

		//

		BitBlt(ps.hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, buffer, 0, 0, SRCCOPY);
		EndPaint(winHandle, &ps);
		return 0;
	case WM_DESTROY:
		DeleteDC(buffer);
		DeleteObject(bitmap);
		ReleaseDC(hwnd, winCon);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void SetWindowClass(WNDCLASSEX& winc)
{
	winc.cbSize = sizeof(winc);
	winc.style = 0;
	winc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winc.hInstance = instance;
	winc.hCursor = LoadCursor(NULL, IDC_ARROW);
	winc.cbClsExtra = 0;
	winc.cbWndExtra = 0;
	winc.hbrBackground = NULL;
	winc.lpszMenuName = WINDOWNAME;
	winc.lpszClassName = CLASSNAME;
	winc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winc.lpfnWndProc = winProc;
}

void MessageLoop()
{
	MSG msg;
	long time, time2;
	time = clock();

	while (1)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				PostQuitMessage(0);
				return;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			continue;
		}
		if ((time2 = clock()) - time < 1000 / 1000)
			continue;
		InvalidateRect(winHandle, NULL, true);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int CmdShow)
{
	WNDCLASSEX winc;
	instance = hInstance;
	SetWindowClass(winc);

	if (!(RegisterClassEx(&winc)))
	{
		PrintError(L"Cannot register class");
		return 0;
	}

	winHandle = CreateWindowEx(NULL, CLASSNAME, WINDOWNAME, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, 0, 0, 
		WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, hInstance, NULL);

	ShowWindow(winHandle, CmdShow);
	UpdateWindow(winHandle);

	//return : quitMessage came
	MessageLoop();
	UnregisterClass(CLASSNAME, hInstance);
	return 0;
}