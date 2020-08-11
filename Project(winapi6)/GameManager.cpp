#include "GameManager.h"
GameManager* GameManager::m_pThis = NULL;

GameManager::GameManager()
{
	match1 = NULL;
	match2 = NULL;
}

void GameManager::Init(HWND hWnd, HINSTANCE hInst)
{
	m_bt.clear();
	HDC hdc = GetDC(hWnd);
	Animal tmp;
	int bmpid = IDB_BITMAP1;
	int x = 700 + CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
	int y = 50 + DRAW_ADD_POINT_Y;
	TCHAR name[128];
	m_bt.reserve(MAX_VALUE);
	m_bt.assign(MAX_VALUE, tmp);
	vector<Animal>::iterator iter = m_bt.begin();
	for (iter; iter != m_bt.end(); iter++)
	{
		(*iter).setbmpid(bmpid);
		(*iter).setPoint(x, y);
		NameFactory(name, bmpid);
		(*iter).setName(name);
		(*iter).setmatchflag(false);
		(*iter).setClickflag(false);
		(*iter).setcompleteflag(false);
		(*iter).Init(hdc, hInst, bmpid);
		x += CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
		if ((*iter).getbmpid() == IDB_BITMAP5 || (*iter).getbmpid() == IDB_BITMAP10)
		{
			x = 700 + CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
			y += CARD_DRAW_SIZE_Y + DRAW_ADD_POINT_Y;
		}
		bmpid++;
		if (bmpid == IDB_BITMAP11) bmpid = IDB_BITMAP1;
	}
}

void GameManager::Draw(HDC hdc)
{
	vector<Animal>::iterator iter = m_bt.begin();
	for (iter; iter != m_bt.end(); iter++)
	{
		(*iter).Draw(hdc);
	}
}

void GameManager::GameInit(HWND hWnd, HINSTANCE hInst)
{
	match1 = NULL;
	match2 = NULL;
	m_game_bt.clear();
	ifstream load;
	char filename[256] = { 0 };
	HDC hdc = GetDC(hWnd);
	Animal tmp; 
	int count = 1;
	int bmpid = IDB_BITMAP1;
	int x = CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
	int y = DRAW_ADD_POINT_Y;
	m_game_bt.reserve(MAX_VALUE * MATCH);
	m_game_bt.assign(MAX_VALUE * MATCH, tmp);
	vector<Animal>::iterator iter = m_game_bt.begin();
	vector<Animal>::iterator iter2 = m_bt.begin();
	sprintf(filename, "Group%d.txt", (rand() % 3) + 1);
	load.open(filename);
	for (iter; iter != m_game_bt.end(); iter++)
	{
		if (load.is_open())
			load >> bmpid;
		(*iter).setbmpid(bmpid);
		(*iter).setPoint(x, y);
		(*iter).setmatchflag(false);
		(*iter).setClickflag(false);
		(*iter).setcompleteflag(false);
		(*iter).Init(hdc, hInst, IDB_BITMAP11);
		x += CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
		if (count != 1 && count % 5 == 0)
		{
			x = CARD_DRAW_SIZE_X + DRAW_ADD_POINT_X;
			y += CARD_DRAW_SIZE_Y + DRAW_ADD_POINT_Y;
		}
		count++;
		bmpid++;
		if (bmpid == IDB_BITMAP11)bmpid = IDB_BITMAP1;
	}
	load.close();
}

void GameManager::GameDraw(HDC hdc)
{
	vector<Animal>::iterator iter = m_game_bt.begin();
	for (iter; iter != m_game_bt.end(); iter++)
	{
		(*iter).Draw(hdc);
	}
}

bool GameManager::FirstClick(HDC hdc, HINSTANCE hInst, int x, int y)
{
	vector<Animal>::iterator iter = m_game_bt.begin();
	if (match1 == NULL)
	{
		for (iter; iter != m_game_bt.end(); iter++)
		{
			if (((*iter).getPoint().x <= x && x <= (*iter).getPoint().x + CARD_DRAW_SIZE_X)
				&& ((*iter).getPoint().y <= y && y <= (*iter).getPoint().y + CARD_DRAW_SIZE_Y))
			{
				if (!(*iter).getcompleteflag())
				{
					if (match1 == NULL)
					{
						(*iter).Init(hdc, hInst, (*iter).getbmpid());
						(*iter).setClickflag(true);
						match1 = &(*iter);
						return true;
					}

				}
			}
		}
	}
	return false;
}

bool GameManager::SecondClick(HDC hdc, HINSTANCE hInst, int x, int y)
{
	vector<Animal>::iterator iter = m_game_bt.begin();
	if (match1 != NULL)
	{
		for (iter; iter != m_game_bt.end(); iter++)
		{
			if (((*iter).getPoint().x <= x && x <= (*iter).getPoint().x + CARD_DRAW_SIZE_X)
				&& ((*iter).getPoint().y <= y && y <= (*iter).getPoint().y + CARD_DRAW_SIZE_Y))
			{
				if (!(*iter).getcompleteflag())
				{
					if (match2 == NULL)
					{
						(*iter).Init(hdc, hInst, (*iter).getbmpid());
						(*iter).setClickflag(true);
						match2 = &(*iter);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameManager::Matching(HDC hdc, HINSTANCE hInst)
{
	vector<Animal>::iterator iter = m_bt.begin();
	if (match1 != NULL && match2 != NULL)
	{
		if ((*match1).getbmpid() == (*match2).getbmpid())
		{
			for (iter; iter != m_bt.end(); iter++)
			{
				if ((*iter).getbmpid() == (*match1).getbmpid())
				{
					(*iter).Init(hdc, hInst, IDB_BITMAP11);
					(*iter).setmatchflag(true);
					(*iter).setcompleteflag(true);
				}
			}
			(*match1).setcompleteflag(true);
			(*match2).setcompleteflag(true);
		}
		else
		{
			(*match1).setClickflag(false);
			(*match2).setClickflag(false);
			(*match1).setmatchflag(false);
			(*match2).setmatchflag(false);
			(*match1).setcompleteflag(false);
			(*match2).setcompleteflag(false);
			(*match1).Init(hdc, hInst, IDB_BITMAP11);
			(*match2).Init(hdc, hInst, IDB_BITMAP11);
		}
		match1 = NULL;
		match2 = NULL;
	}
}

bool GameManager::GameCheck()
{
	int count = 0;
	vector<Animal>::iterator iter = m_bt.begin();
	for (iter; iter != m_bt.end(); iter++)
	{
		if ((*iter).getmatchflag())
		{
			count++;
		}
	}
	if (count >= MAX_VALUE)
		return true;
	else return false;
}

void GameManager::NameFactory(TCHAR name[], int bmpid)
{
	switch (bmpid)
	{
	case IDB_BITMAP1:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP2:
		wsprintf(name, TEXT("ȣ����"));
		break;
	case IDB_BITMAP3:
		wsprintf(name, TEXT("����"));
		break;
	case IDB_BITMAP4:
		wsprintf(name, TEXT("�ڳ���"));
		break;
	case IDB_BITMAP5:
		wsprintf(name, TEXT("��"));
		break;
	case IDB_BITMAP6:
		wsprintf(name, TEXT("��"));
		break;
	case IDB_BITMAP7:
		wsprintf(name, TEXT("�����"));
		break;
	case IDB_BITMAP8:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP9:
		wsprintf(name, TEXT("������"));
		break;
	case IDB_BITMAP10:
		wsprintf(name, TEXT("��"));
		break;
	default:
		break;
	}
}

void GameManager::Release()
{
	delete m_pThis;
}

GameManager::~GameManager()
{
	m_bt.clear();
	m_game_bt.clear();
}