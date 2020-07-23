#include "Interface.h"

Interface* Interface::m_interface_this = NULL;

Interface::Interface()
{
	m_istage = 1;
}

void Interface::GameTitle()
{
	char buf[256];
	sprintf(buf, "mode con: lines=%d cols=%d", Y + 4, (X * 2) + 1);
	system(buf);
	SKY_BLUE
		BoxDraw(0, 0, X, 35);
	ORIGINAL
	BLUE
		DrawMidText("☆ ★ 베 네 치 아 ★ ☆", X, 7);
		DrawMidText("1.Game Start", X, 14);
		DrawMidText("2.Rank", X, 17);
		DrawMidText("3.Exit", X, 20);
	ORIGINAL
	
}

void Interface::InfoDraw(int life, int score, string name)
{
	for (int i = 0; i < X; i++)
		DrawPoint("  ", 0 + i, Y + 2);
	RED
	DrawPoint("Life : ", 1, Y + 2);
	for (int i = 0; i < life; i++)
	{
		cout << "♥";
	}
	DrawMidText("Score : " + to_string(score), X, Y + 2);
	DrawPoint("Name : " + name, X - 9, Y + 2);
	ORIGINAL
}

void Interface::GameScroll()
{
	char ch;
	int i = 0;
	int y = 6;
	int story_max = 0;
	string scroll;
	list<string> allscroll;
	list<string>::iterator iter;
	list<string>::iterator view_iter;
	ifstream load;
	int oldclock = clock();
	load.open("benechia_story.txt");
	if (load.is_open())
	{
		load >> story_max;
		while (!load.eof())
		{
			getline(load, scroll);
			allscroll.push_back(scroll);
		}
		iter = allscroll.begin();
		BLUE
			while (story_max > 0)
			{
				if (kbhit())
				{
					if (getch() == 's' || getch() == 'S')
						break;
				}
				if (clock() - oldclock >= SCROLL_TIME)
				{
					if (story_max > 16)
					{
						scroll = (*iter);
						DrawMidText(scroll, X, y);
						iter++;
						y++;
					}
					else
					{
						if (story_max == 16)
						{
							iter = allscroll.begin();
							iter++;
						}
						y = 6;
						view_iter = iter;
						for (i = 0; i < MAX_SCROLL; i++)
						{
							scroll = (*view_iter);
							DrawMidText("                                                      ", X, y);
							DrawMidText(scroll, X, y);
							view_iter++;
							y++;
							DrawMidText("                                                      ", X, y);
						}
						iter++;
					}
					oldclock = clock();
					story_max--;
				}
			}
		ORIGINAL
	}
	load.close();
}

void Interface::ShowStage(int& stage)
{
	int oldclock = clock();
	BLUE
	DrawMidText("★ " + to_string(stage) + " Stage ★", X, Y / 2 - 1);
	ORIGINAL
	while (true)
	{
		if (clock() - oldclock >= 3000)
		{
			DrawMidText("                           ", X, Y / 2 - 1);
			break;
		}
		if (kbhit())
		{
			DrawMidText("                           ", X, Y / 2 - 1);
			break;
		}	
	}
}