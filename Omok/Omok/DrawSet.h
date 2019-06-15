#pragma once

#include <Windows.h>

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
private:
	HBITMAP bitmap;
};