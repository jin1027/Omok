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
	Set(loc.x, loc.y);
}
bool Omok::Set(int x, int y)
{
	//TODO
}
//don't Null.
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