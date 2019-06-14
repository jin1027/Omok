#include "Omok.h"



Omok::Omok()
{
	this->NewGame();
}


Omok::~Omok()
{
}


void Omok::InitializeBoard()
{
	int i, j;
	for (i = 0; i < boardLen; i++)
		for (j = 0; j < boardLen; j++)
			board[i][j] = Color::Null;
}


void Omok::NewGame()
{
	this->InitializeBoard();
	now = Color::BLACK;
}

bool Omok::Set(Location loc)
{
	return Set(loc.x, loc.y);
}

bool Omok::Set(int x, int y)
{
	if (board[x][y] != Color::Null)
		return false;
	return CanSetAsRenzu(x, y, now);
}

void Omok::SetNow(Color c)
{
	now = c;
}
Color Omok::GetNow()
{
	return now;
}

void Omok::ColorChange()
{
	if (now == Color::BLACK)
		now = Color::WHITE;
	else
		now = Color::BLACK;
	return;
}

bool Omok::CanSetAsRenzu(int x, int y, Color now)
{
	if (now == Color::Null)
		return false;
	if (now == Color::BLACK)//check 3,3 or 4,4
	{

	}
	int count = 0;
	

	return false;
}

int Omok::CountLine(int fromX, int fromY, int dirX, int dirY, Color now)
{
	int count = 0;
	int re;
	Color color;

	for (re = 1; re <= 3; re++)
	{
		color = board[fromX + dirX * re][fromY + dirY * re];
		if (color == now)
		{
			count++;
			continue;
		}
		else if (color != Color::Null)
			return count;
	}
	return count;
}

int Omok::CountLongLine(int fromX, int fromY, int dirX, int dirY, Color now)
{

	return 0;
}

bool Omok::IsInvalidLoc(int x, int y)
{
	return (x < 0) || (x >= boardLen) || (y < 0) || (y >= boardLen);
}
