#include <Windows.h>
#include <random>
#include <time.h>
#include <math.h>

#include "DrawSet.h"
#include "Location.h"
#include "Omok.h"
#include "OmokView.h"

#pragma comment(lib, "msimg32.lib")

Omok omok;
OmokView view;

const wchar_t CLASSNAME[] = L"Omok";
const wchar_t WINDOWNAME[] = L"Omok";

const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 960;

Location buttonDownAt(0, 0);

//double buffering

DrawSet buffer;
HWND winHandle;
HDC winCon;
HINSTANCE instance;

//by messageBox
void PrintError(const wchar_t* err)
{
	MessageBox(winHandle, err, L"ERROR", MB_OK);
}

void ReDraw()
{
	InvalidateRect(winHandle, NULL, true);
}

LRESULT CALLBACK winProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
		winCon = GetDC(hwnd);
		buffer.Initialize(winCon, WINDOW_WIDTH, WINDOW_HEIGHT);
		view.Initialize(winCon);
		return 0;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(winHandle, &ps);
		BitBlt(buffer.hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, 0, 0, WHITENESS);

		view.View(buffer.hdc, omok);

		BitBlt(ps.hdc, 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, buffer.hdc, 0, 0, SRCCOPY);
		EndPaint(winHandle, &ps);
		return 0;
	case WM_LBUTTONDOWN:
	{
		int x = LOWORD(lParam);
		int y = HIWORD(lParam);

		x = view.MonitorToArray(x);
		y = view.MonitorToArray(y);

		omok.Set(x, y);
		ReDraw();
	}
		return 0;
	case WM_KEYDOWN:
		if (wParam == VK_SPACE)
		{
			ReDraw();
		}
		return 0;
	case WM_DESTROY:
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

	while (GetMessage(&msg, NULL, 0, 0))
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