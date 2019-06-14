#pragma once

#include "Location.h"

enum class Color
{
	BLACK, WHITE, Null
};
const int boardLen = 19;
class Omok
{
public:
	Omok();
	~Omok();

	void NewGame();
	//board[x][y];
	bool Set(Location);
	//board[x][y];
	bool Set(int x, int y);
	//don't Null.
	void SetNow(Color);
	Color GetNow();
private:
	Color board[boardLen][boardLen];
	Color now;

	void InitializeBoard();
	void ColorChange();
};