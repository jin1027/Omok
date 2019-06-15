#include "DrawSet.h"


DrawSet::~DrawSet()
{
	DeleteDC(hdc);
	DeleteObject(bitmap);
}

void DrawSet::Initialize(HDC& hdc, int sizeX, int sizeY)
{
	this->hdc = CreateCompatibleDC(hdc);
	bitmap = CreateCompatibleBitmap(hdc, sizeX, sizeY);
	SelectObject(this->hdc, bitmap);
}