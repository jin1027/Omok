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
	if (IsInvalidLoc(x, y))
		return false;
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
	count += CountLine(x, y, 1, 0, now);
	count += CountLine(x, y, -1, 0, now);


	return false;
}

int Omok::CountLine(int fromX, int fromY, int dirX, int dirY, Color now)
{
	int count = 0;
	int re;
	Color color;

	int tempX = fromX;
	int tempY = fromY;

	for (int reverse = 0; reverse < 2; reverse++)
	{
		for (re = 1; ; re++)
		{
			fromX += dirX;
			fromY += dirY;

			if (IsInvalidLoc(fromX, fromY))
				break;

			color = board[fromX][fromY];
			if (color == now)
			{
				count++;
				continue;
			}
			else if (color != Color::Null)
				break;
			else
				break;
		}

		fromX = tempX;
		fromY = tempY;
		dirX = -dirX;
		dirY = -dirY;
	}
	return count;
}

int Omok::CountLongLine(int fromX, int fromY, int dirX, int dirY, Color now)
{
	int count = 0;
	int re;
	Color color;

	int tempX = fromX;
	int tempY = fromY;

	for (int reverse = 0; reverse < 2; reverse++)
	{
		for (re = 1; ; re++)
		{
			fromX += dirX;
			fromY += dirY;

			if (IsInvalidLoc(fromX, fromY))
				break;

			color = board[fromX][fromY];
			if (color == now)
			{
				count++;
				continue;
			}
			else if (color == Color::Null)
				continue;
			else
				break;
		}

		fromX = tempX;
		fromY = tempY;
		dirX = -dirX;
		dirY = -dirY;
	}
	return count;
}

bool Omok::IsInvalidLoc(int x, int y)
{
	return (x < 0) || (x >= boardLen) || (y < 0) || (y >= boardLen);
}
