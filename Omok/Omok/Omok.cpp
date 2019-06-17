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
	gameEnd = false;
	winner = Color::Null;
}

bool Omok::Set(Location loc)
{
	return Set(loc.x, loc.y);
}

bool Omok::Set(int x, int y)
{
	if (gameEnd)
		return false;
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

Color Omok::GetWinner()
{
	return winner;
}

bool Omok::IsGameEnd()
{
	return gameEnd;
}

void Omok::ChangeNow()
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
	int count = 0;
	bool is3344 = false;
	if (now == Color::BLACK)//check 3,3 or 4,4
	{
		int is3 = 0;
		int is4 = 0;

		count = Check3344(x, y, 1, 0, now);
		if (count == 3)
			is3++;
		if (count == 4)
			is4++;
		count = Check3344(x, y, 0, 1, now);
		if (count == 3)
			is3++;
		if (count == 4)
			is4++;
		count = Check3344(x, y, 1, 1, now);
		if (count == 3)
			is3++;
		if (count == 4)
			is4++;
		count = Check3344(x, y, 1, -1, now);
		if (count == 3)
			is3++;
		if (count == 4)
			is4++;

		if (is3 >= 2 || is4 >= 2)
			is3344 = true;
	}

	//check win?
	if (now == Color::BLACK)
	{
		count = CountLine(x, y, 1, 0, now);
		if (count == 5)
			goto win;
		count = CountLine(x, y, 0, 1, now);
		if (count == 5)
			goto win;
		count = CountLine(x, y, 1, 1, now);
		if (count == 5)
			goto win;
		count = CountLine(x, y, 1, -1, now);
		if (count == 5)
			goto win;
		if (is3344)
			return false;
	}
	else
	{
		count = CountLine(x, y, 1, 0, now);
		if (count >= 5)
			goto win;
		count = CountLine(x, y, 0, 1, now);
		if (count >= 5)
			goto win;
		count = CountLine(x, y, 1, 1, now);
		if (count >= 5)
			goto win;
		count = CountLine(x, y, 1, -1, now);
		if (count >= 5)
			goto win;
	}

	board[x][y] = now;
	ChangeNow();

	return false;
win:
	board[x][y] = now;
	gameEnd = true;
	winner = now;
	return true;
}

int Omok::CountLine(int fromX, int fromY, int dirX, int dirY, Color now)
{
	int count = 1;//don't check fromX, fromY
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

int Omok::Check3344(int fromX, int fromY, int dirX, int dirY, Color now)
{
	int count = 1;//don't check fromX, fromY
	int re;
	int nullWas = 0;
	Color color;

	int tempX = fromX;
	int tempY = fromY;

	for (int reverse = 0; reverse < 2; reverse++)//reverse don't use.
	{
		for (re = 1; true; re++)
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
			{
				if (nullWas)//if null exist 2, it is not 33 or 44 condition.
					break;
				nullWas = re;
				continue;
			}
			else//other color
				if (re - 1 == nullWas)//before was space. now will check opposite dir, or break;
					break;
				else//it is blocked 3 or 4
					return 0;
		}

		fromX = tempX;
		fromY = tempY;
		dirX = -dirX;
		dirY = -dirY;
		nullWas = 0;
	}
	return count;
}

bool Omok::IsInvalidLoc(int x, int y)
{
	return (x < 0) || (x >= boardLen) || (y < 0) || (y >= boardLen);
}
