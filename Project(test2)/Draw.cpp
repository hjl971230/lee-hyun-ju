#include "Draw.h"

Draw::Draw()
{

}


void Draw::MapDraw(int Width, int Height)
{
	for (int y = 0; y < Height; y++)
	{
		for (int x = 0; x < Width; x++)
		{
			cout << "¢Ë";
		}
		cout << endl;
	}
	return;
}

void Draw::DrawPoint(string str, int x, int y)
{
	gotoxy(x * 2, y);
	cout << str;
	gotoxy(-1, -1);
	return;
}

void Draw::DrawMidText(string str, int x, int y)
{
	if (x > str.size() / 2)
		x -= str.size() / 2;
	gotoxy(x, y);
	cout << str;
	return;
}


void Draw::BoxDraw(int Start_x, int Start_y, int Width, int Height)
{
	if (Start_x > Width)
		Start_x -= Width;
	for (int y = 0; y < Height; y++)
	{
		gotoxy(Start_x, Start_y + y);
		if (y == 0)
		{
			cout << "¢Ë";
			for (int x = 1; x < Width - 1; x++)
				cout << "¢Ë";
			cout << "¢Ë";
		}
		else if (y == Height - 1)
		{
			cout << "¢Ë";
			for (int x = 1; x < Width - 1; x++)
				cout << "¢Ë";
			cout << "¢Ë";
		}
		else
		{
			cout << "¢Ë";
			for (int x = 1; x < Width - 1; x++)
				cout << "  ";
			cout << "¢Ë";
		}
	}
	return;
}

void Draw::ErasePoint(int x, int y)
{
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(-1, -1);
	return;
}
void Draw::Erase(int x, int y, string str)
{
	gotoxy(x * 2, y);
	cout << str;
	return;
}

Draw::~Draw()
{
}