#pragma once

#include "Location.h"

enum class Color
{
	BLACK, WHITE, Null
};
const int boardLen = 15;
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
	Color GetWinner();
	bool IsGameEnd();
private:
	Color board[boardLen][boardLen];
	Color now;
	bool gameEnd = true;
	Color winner = Color::Null;

	void InitializeBoard();
	void ColorChange();

	bool CanSetAsRenzu(int x, int y, Color now);
	//if Color::Null || other color    break;
	//it also count opposite dir.
	int CountLine(int fromX, int fromY, int dirX, int dirY, Color now);
	//if other color	 break;
	//it also count opposite dir.
	int CountLongLine(int fromX, int fromY, int dirX, int dirY, Color now);
	bool IsInvalidLoc(int x, int y);
};