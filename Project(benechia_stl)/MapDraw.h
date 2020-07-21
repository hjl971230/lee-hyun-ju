#pragma once
#include"Mecro.h"
#define UP 'w'
#define DOWN 's'
#define ENTER 13
class MapDraw
{
private:
	static MapDraw* m_MapDraw_this;
public:
	static MapDraw* GetInstance()
	{
		if (m_MapDraw_this == NULL)
			m_MapDraw_this = new MapDraw;
		return m_MapDraw_this;
	}
	void BoxDraw(int Start_x,int Start_y, int Width, int Height);
	void BoxErase(int Width, int Height);
	void DrawPoint(string str, int x, int y);
	void DrawMidText(string str, int x, int y);
	void TextDraw(string str, int x, int y);
	void ErasePoint(int x, int y);
	int MenuSelectCursor(int MenuLen, int AddCol, int x, int y);
	MapDraw();
	virtual ~MapDraw();
};

