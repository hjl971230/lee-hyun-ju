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
	//string allscroll[MAX_SCROLL];
	list<string> allscroll;
	list<string> viewline;
	list<string>::iterator view_iter = viewline.begin();
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
		BLUE
			while (story_max > 0)
			{
				if (kbhit())
				{
					if (getch() == 's' || getch() == 'S')
						break;
				}
				if (story_max > 16)
				{
					while (true)
					{
						if (clock() - oldclock >= 1000)
						{
							//allscroll[i] = scroll;
							//DrawMidText(allscroll[i], X, y);
							viewline.push_back(allscroll.front());
							DrawMidText(*view_iter, X, y);
							view_iter++;
							allscroll.pop_front();
							oldclock = clock();
							break;
						}
					}
					y++;
					//i++;
				}
				else
				{
					y = 6;
					for (i = 0; i < MAX_SCROLL; i++)
					{
						if (i < MAX_SCROLL - 1)
						{
							viewline.push_back(allscroll.front());
							allscroll.pop_front();
						}
							//allscroll[i] = allscroll[i + 1];
						else
						{
							//getline(load, scroll);
							//allscroll[MAX_SCROLL - 1] = scroll;
						}
					}
					while (true)
					{
						if (clock() - oldclock >= 1000)
						{
							for (i = 0; i < MAX_SCROLL; i++)
							{
								if(i==0)
									DrawMidText("                                                      ", X, y);
								//DrawMidText(allscroll[i], X, y);
								y++;
								DrawMidText("                                                      ", X, y);
							}
							oldclock = clock();
							break;
						}
					}
				}
				story_max--;
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