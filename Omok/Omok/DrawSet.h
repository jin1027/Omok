#pragma once

#include <Windows.h>
#include "include.h"

class DrawSet
{
	//At first, should Initialize();

	//auto : create compatibleDC, deleteDC
	//auto : make bitmap, delete bitmap
public:
	HDC hdc;

	DrawSet() = default;
	~DrawSet();
	//it use hdc for CreateCompatibleDC
	//it initialize hdc, bitmap
	// size : you hope
	void Initialize(HDC& hdc, int sizeX, int sizeY);

	//draw circle, O(r,r), radius = r;
	//out of circle, fill with invisible
	void DrawCircle(Real radius, COLORREF color, COLORREF invisible);
private:
	HBITMAP bitmap;
};