#pragma once
#include"header.h"

class Draw
{
public:
	Draw();
	virtual ~Draw();
	inline void gotoxy(int x, int y)
	{
		COORD Pos = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	}
	void Erase(int x, int y, string str);
	void BoxDraw(int Start_x, int Start_y, int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void MapDraw(int Width, int Height);
	void ErasePoint(int x, int y);
};

