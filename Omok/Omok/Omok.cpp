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
	//TODO
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

bool Omok::CanSetAsRenzu()
{
	return false;
}

int Omok::CountLine(int fromX, int fromY, int dirX, int dirY)
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