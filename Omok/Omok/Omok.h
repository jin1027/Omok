#pragma once

#include "Location.h"

enum class Color
{
	BLACK, WHITE, Null
};

extern "C" 
{
	const int boardLen = 15;
}

class Omok
{
	friend class OmokView;
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
	void ChangeNow();

	bool CanSetAsRenzu(int x, int y, Color now);
	//if Color::Null || other color    break;
	//it also count opposite dir.
	int CountLine(int fromX, int fromY, int dirX, int dirY, Color now);
	/*
	if other color	 return 0;
	if Null color  continue
	Null can only one
	it also count opposite dir.
	1
	only call for check 33, 44
	*/
	int Check3344(int fromX, int fromY, int dirX, int dirY, Color now);
	bool IsInvalidLoc(int x, int y);
};