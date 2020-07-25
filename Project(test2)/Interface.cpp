#include "Interface.h"

Interface* Interface::m_Interface_this = NULL;

Interface::Interface()
{
	//¢Ë : ºí·Ï ¢Í : ÆøÆÄ ¢Á : ÇÃ·¹ÀÌ¾î ¢Â : ±ê¹ß ¢Ã : Áö·Ú
}

Interface::~Interface()
{

}

void Interface::MainMenu()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", WINDOW_HEIGHT + 5, (WINDOW_WIDTH * 2) + 1);
	system(buf);
	BoxDraw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	DrawMidText(" ¢Ã MINESWEEPER ¢Ã ", WINDOW_WIDTH, WINDOW_HEIGHT * 0.3);
	DrawMidText("1. Game Start", WINDOW_WIDTH, WINDOW_HEIGHT * 0.4);
	DrawMidText("2. Level Select", WINDOW_WIDTH, WINDOW_HEIGHT * 0.5);
	DrawMidText("3. Exit", WINDOW_WIDTH, WINDOW_HEIGHT * 0.6);
	BoxDraw(WINDOW_WIDTH, WINDOW_HEIGHT * 0.7, WINDOW_WIDTH * 0.2, 3);
	gotoxy(WINDOW_WIDTH, WINDOW_HEIGHT * 0.7 + 1);
}

void Interface::selectLevel()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", WINDOW_HEIGHT + 5, (WINDOW_WIDTH * 2) + 1);
	system(buf);
	BoxDraw(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	DrawMidText(" ¢Ã LEVEL SELECT ¢Ã ", WINDOW_WIDTH, WINDOW_HEIGHT * 0.3);
	DrawMidText("1. Easy (10 * 10) Mine : 10", WINDOW_WIDTH, WINDOW_HEIGHT * 0.4);
	DrawMidText("2. Normal (30 * 30) Mine : 30", WINDOW_WIDTH, WINDOW_HEIGHT * 0.5);
	DrawMidText("3. Hard (50 * 50) Mine : 50", WINDOW_WIDTH, WINDOW_HEIGHT * 0.6);
	DrawMidText("4. Exit", WINDOW_WIDTH, WINDOW_HEIGHT * 0.7);
	BoxDraw(WINDOW_WIDTH, WINDOW_HEIGHT * 0.8, WINDOW_WIDTH * 0.2, 3);
	gotoxy(WINDOW_WIDTH, WINDOW_HEIGHT * 0.8 + 1);
}

void Interface::GameDraw(int width, int height)
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", height + 10, (width * 2) + 10);
	system(buf);
	MapDraw(width, height);
}

void Interface::GameResult(RESULT res, int width, int height)
{
	if(res == RESULT_CLEAR)
		DrawMidText(" ¢Â ¢Â ¢Â GAME CLEAR ¢Â ¢Â ¢Â ", width, height + 5);
	else if(res == RESULT_BOOM)
		DrawMidText(" ¢Í ¢Í ¢Í GAME OVER ¢Í ¢Í ¢Í ", width, height + 5);
	gotoxy(WINDOW_WIDTH, WINDOW_HEIGHT * 0.8);
}

void Interface::vecmapDraw(vector<vector< Blockinfo>> map)
{
	system("cls");
	for (vector<vector<Blockinfo>>::iterator iter_height = map.begin(); iter_height != map.end(); iter_height++)
	{
		for (vector<Blockinfo>::iterator iter_width = (*iter_height).begin(); iter_width != (*iter_height).end(); iter_width++)
		{
			if (!(*iter_width).hideflag)
				cout << (*iter_width).Blockshape;
			else
				cout << "¢Ë";
		}
		cout << endl;
	}
}

void Interface::info(int& mine, int& count, int width, int height)
{
	DrawMidText("mine : " + to_string(mine), width, height + 5);
	DrawMidText("find : " + to_string(count), width, height + 6);
	DrawMidText("¡è : w    ¡é : s    ¡ç : a    ¡æ : d ", width, height + 7);
	DrawMidText("flag : space   flag cancel : z", width, height + 8);
}