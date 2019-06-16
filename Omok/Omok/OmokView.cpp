#include "OmokView.h"

void OmokView::Initialize(HDC hdc)
{
	//204 102 0
	{
		board.Initialize(hdc, boardSize, boardSize);
		SetPixel(board.hdc, 0, 0, boardColor);
		StretchBlt(board.hdc, 0, 0, boardSize, boardSize, board.hdc, 0, 0, 1, 1, SRCCOPY);

		HDC& boardHDC = board.hdc;
		int x;
		int from;
		int radius = stoneSize / 2;
		const int monitorX0 = ArrayToMonitor(0) + radius;
		const int monitorY0 = ArrayToMonitor(0) + radius;
		const int monitorXmax = ArrayToMonitor(boardLen - 1) + radius;
		const int monitorYmax = ArrayToMonitor(boardLen - 1) + radius;
		for (x = 0; x < boardLen; x++)
		{
			from = ArrayToMonitor(x) + radius;

			MoveToEx(boardHDC, from, monitorY0, NULL);
			LineTo(boardHDC, from, monitorYmax);

			MoveToEx(boardHDC, monitorY0, from, NULL);
			LineTo(boardHDC, monitorYmax, from);
		}
	}

	white.Initialize(hdc, stoneSize, stoneSize);
	white.DrawCircle(stoneSize / 2, RGB(255, 255, 255), invisible);

	black.Initialize(hdc, stoneSize, stoneSize);
	black.DrawCircle(stoneSize / 2, RGB(0, 0, 0), invisible);


}

void OmokView::View(HDC buffer, Omok& omok)
{
	BitBlt(buffer, 0, 0, boardSize, boardSize, board.hdc, 0, 0, SRCCOPY);

	int x, y;
	int toX, toY;
	DrawSet* draw;
	for (x = 0; x < boardLen; x++)
		for (y = 0; y < boardLen; y++)
		{
			if (omok.board[x][y] == Color::BLACK)
				draw = &white;
			else if (omok.board[x][y] == Color::WHITE)
				draw = &black;
			else
				continue;

			toX = ArrayToMonitor(x);
			toY = ArrayToMonitor(y);
			TransparentBlt(buffer, toX, toY, stoneSize, stoneSize, draw->hdc, 0, 0, stoneSize, stoneSize, invisible);
		}
}

int OmokView::ArrayToMonitor(int x)
{
	return space + x * (space + stoneSize);
}

int OmokView::MonitorToArray(int x)
{
	return (x - space) / (space + stoneSize);
}
