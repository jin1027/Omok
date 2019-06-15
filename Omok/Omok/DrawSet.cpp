#include "DrawSet.h"
#include <math.h>


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

void DrawSet::DrawCircle(Real r, COLORREF color, COLORREF invisible)
{
	int x, y;

	for (x = 0; x < r * 2; x++)
		for (y = 0; y < r * 2; y++)
		{
			Real xDis = x - r;
			Real yDis = y - r;
			Real distance = sqrt(xDis * xDis + yDis * yDis);

			if (distance <= r)
				SetPixel(hdc, x, y, WHITENESS);
			else
				SetPixel(hdc, x, y, invisible);
		}
}
