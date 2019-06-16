#pragma once

#include <Windows.h>
#include <math.h>

#include "DrawSet.h"
#include "Omok.h"


const int space = 10;
const int stoneSize = 30;
const int boardSize = boardLen * (stoneSize + space) + space;

const COLORREF boardColor = RGB(204, 102, 0);
const COLORREF invisible = RGB(255, 0, 255);

//At first, you should call initialize
class OmokView
{
public:
	OmokView() = default;
	~OmokView() = default;

	//it need hdc for CreateCompatibleDC()
	void Initialize(HDC hdc);

	void View(HDC, Omok&);

	int ArrayToMonitor(int);
	int MonitorToArray(int);
private:
	DrawSet board;
	DrawSet white;
	DrawSet black;
};
