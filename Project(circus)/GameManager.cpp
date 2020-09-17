#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_ibacksize = 0;
	m_idecosize = 0;
	m_inormalcount = 0;
	m_imitercount = 0;
	m_imiter = 100;
	wsprintf(nowMiter, TEXT("%d"), m_imiter);
	m_imovemiter = 0;
	m_bwinflag = false;
	m_iNormal_ver = BG_CODE_NORMAL;
	m_bgameflag = false;
}

GameManager::~GameManager()
{
	delete EnemyManager::GetInstance();
	delete Player::GetInstance();
}

void GameManager::GameInit(HDC hdc, HINSTANCE hInst)
{
	m_ibacksize = 0;
	m_idecosize = 0;
	m_inormalcount = 0;
	m_imitercount = 0;
	m_imiter = 100;
	wsprintf(nowMiter, TEXT("%d"), m_imiter);
	m_imovemiter = 0;
	m_bwinflag = false;
	m_iNormal_ver = BG_CODE_NORMAL;
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_BG[BG_CODE_BACK].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_DECO].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_deco.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_normal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL2].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_normal2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	End.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\end.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Icon.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\icon.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_Miter.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\miter.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Star[0].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\star.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Star[1].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\star1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Star[2].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\star2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Player::GetInstance()->Init(m_BitMap.getMemDC(), hInst);
	EnemyManager::GetInstance()->Init(m_BitMap.getMemDC(), hInst);
	StartButton = { 570,400,670,413 };
	ExitButton = { 570,450,670,463 };
}

void GameManager::GameDraw(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	BGDraw(m_BitMap.getMemDC());
	End.Draw(m_BitMap.getMemDC(), ((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter, 600);
	EnemyManager::GetInstance()->Draw(m_BitMap.getMemDC());
	EnemyManager::GetInstance()->B_Draw(m_BitMap.getMemDC());
	Player::GetInstance()->Draw(m_BitMap.getMemDC());
	EnemyManager::GetInstance()->F_Draw(m_BitMap.getMemDC());
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::GameTitle(HDC hdc, HINSTANCE hInst)
{
	int starnum = 0;
	RECT rt = { BOX_SIZE_X + (Star[1].getsize().cx * 10),BOX_SIZE_Y + (Star[1].getsize().cy * 7),BOX_SIZE_X + (Star[1].getsize().cx * 40),BOX_SIZE_Y + (Star[1].getsize().cy * 10) };
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	for (int i = BOX_SIZE_X; i <= BOX_SIZE_X + (Star[1].getsize().cx * 50); i+= Star[1].getsize().cx)
	{
		for (int j = BOX_SIZE_Y; j <= BOX_SIZE_Y + (Star[1].getsize().cy * 15); j+= Star[1].getsize().cy)
		{
			if (i == BOX_SIZE_X || j == BOX_SIZE_Y || i == BOX_SIZE_X + (Star[starnum].getsize().cx * 50) || j == BOX_SIZE_Y + (Star[starnum].getsize().cy * 15))
			{
				Star[starnum].Draw(m_BitMap.getMemDC(), i, j);
			}
			starnum++;
			if (starnum >= 3) starnum = 0;
		}
	}
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
	DrawText(hdc, TEXT("C I R C U S"), -1, &rt, DT_CENTER | DT_WORDBREAK);
	DrawText(hdc, TEXT("  Game   Start"), -1, &StartButton, DT_CENTER | DT_WORDBREAK);
	DrawText(hdc, TEXT(" Game      Exit "), -1, &ExitButton, DT_CENTER | DT_WORDBREAK);
	if (PtInRect(&StartButton, mouse))
		m_bgameflag = true;
	if (PtInRect(&ExitButton, mouse))
		PostQuitMessage(0);
}

void GameManager::ScoreLifeDraw(HDC hdc)
{
	int score_x = Star[1].getsize().cx + 10;
	int life_x = 1200;
	int y = 60;
	TCHAR lifetext[128] = "Life";
	TCHAR scoretext[128] = "Score : ";
	wsprintf(scoretext, TEXT("Score : %d"), Player::GetInstance()->getscore());
	TextOut(hdc, score_x, y, scoretext, lstrlen(scoretext));
	TextOut(hdc, life_x - lstrlen(lifetext), y / 2, lifetext, lstrlen(lifetext));
	for (int i = 0; i < Player::GetInstance()->getlife(); i++)
	{
		Icon.Draw(hdc, life_x, y, 2);
		life_x -= (Icon.getsize().cx + 50);
	}
	int starnum = 0;
	for (int i = 0; i <= (Star[1].getsize().cx * 100); i += Star[1].getsize().cx)
	{
		for (int j = 0; j <= (Star[1].getsize().cy * 15); j += Star[1].getsize().cy)
		{
			if (i == 0 || j == 0 || i == (Star[starnum].getsize().cx * 100) || j == (Star[starnum].getsize().cy * 15))
			{
				Star[starnum].Draw(m_BitMap.getMemDC(), i, j);
			}
			starnum++;
			if (starnum >= 3) starnum = 0;
		}
	}
}

void GameManager::BGDraw(HDC hdc)
{
	ScoreLifeDraw(m_BitMap.getMemDC());
	while (m_ibacksize <= 1800 || m_idecosize <= 1800)
	{
		if (m_imitercount % 10 == 0)
		{
			if (m_imiter >= 0)
			{
				m_Miter.Draw(hdc, m_ibacksize, 670);
				wsprintf(nowMiter, TEXT("%d"), m_imiter);
				TextOut(hdc, m_ibacksize + 25, 675, nowMiter, lstrlen(nowMiter));
				m_imitercount = 0;
				m_imiter -= 10;
			}
		}
		m_BG[BG_CODE_BACK].Draw(hdc, m_ibacksize, 480);
		if (m_inormalcount < 12)
		{
			m_BG[m_iNormal_ver].Draw(hdc, m_idecosize, 416);
			m_idecosize += m_BG[m_iNormal_ver].getsize().cx;
			m_inormalcount++;
		}
		else
		{
			m_BG[BG_CODE_DECO].Draw(hdc, m_idecosize, 413);
			m_idecosize += m_BG[BG_CODE_DECO].getsize().cx;
			m_inormalcount = 0;
		}
		m_ibacksize += m_BG[BG_CODE_BACK].getsize().cx;
		m_imitercount++;
	}
	m_ibacksize = 0 + m_imovemiter;
	m_idecosize = 0 + m_imovemiter;
	m_inormalcount = 0;
	m_imitercount = 0;
	m_imiter = 100;
	wsprintf(nowMiter, TEXT("%d"), m_imiter);
}

void GameManager::Update(HDC hdc, HWND hWnd, HINSTANCE hInst)
{
	EnemyManager::GetInstance()->Update();
	if (EnemyManager::GetInstance()->CollideCheck(Player::GetInstance()->getcollider()))
		Die(hdc, hWnd, hInst);
	if (finishcheck())
	{
		Win(hdc, hWnd, hInst);
	}
}

void GameManager::Win(HDC hdc, HWND hWnd, HINSTANCE hInst)
{
	int drawcount = 10;
	m_bwinflag = true;
	EnemyManager::GetInstance()->release();
	while (drawcount > 0)
	{
		Sleep(300);
		Player::GetInstance()->setx(((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter + 10);
		Player::GetInstance()->sety((600 - (Player::GetInstance()->getWinMotionBitMap().getsize().cy)));
		m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
		BGDraw(m_BitMap.getMemDC());
		End.Draw(m_BitMap.getMemDC(), ((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter, 600);
		Player::GetInstance()->WinDraw(m_BitMap.getMemDC());
		BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
		drawcount--;
		if (m_iNormal_ver == BG_CODE_NORMAL2) m_iNormal_ver = BG_CODE_NORMAL;
		else m_iNormal_ver = BG_CODE_NORMAL2;
	}
	if ((MessageBox(hWnd, TEXT("게임을 다시 하시겠습니까?"), TEXT("Game Clear"), MB_YESNO) == IDYES))
	{
		GameInit(hdc, hInst);
	}
	else
	{
		m_bgameflag = false;
	}
}

void GameManager::Die(HDC hdc, HWND hWnd, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_iNormal_ver = BG_CODE_NORMAL2;
	BGDraw(m_BitMap.getMemDC());
	EnemyManager::GetInstance()->Draw(m_BitMap.getMemDC());
	End.Draw(m_BitMap.getMemDC(), ((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter, 600);
	EnemyManager::GetInstance()->B_Draw(m_BitMap.getMemDC());
	Player::GetInstance()->DieDraw(m_BitMap.getMemDC());
	EnemyManager::GetInstance()->F_Draw(m_BitMap.getMemDC());
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
	Sleep(2000);
	EnemyManager::GetInstance()->release();
	GameInit(hdc, hInst);
	Player::GetInstance()->lifedown();
	if (Player::GetInstance()->getlife() <= 0)GameOver(hdc, hInst);
}

void GameManager::GameOver(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	TCHAR text[128] = "Game Over";
	TextOut(m_BitMap.getMemDC(), 700, 400, text, lstrlen(text));
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
	Sleep(2000);
	m_bgameflag = false;
	mouse.x = 0;
	mouse.y = 0;
	Player::GetInstance()->setlife(3);
	Player::GetInstance()->setscore(0);
}

bool GameManager::finishcheck()
{
	RECT EndCollider = { ((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter, 600 ,((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter + End.getsize().cx, 600 + End.getsize().cy};
	if (PtInRect(&EndCollider, Player::GetInstance()->getPoint()))
		return true;
	else return false;
}

void GameManager::PlayGame()
{
	KeyInput();
	Player::GetInstance()->KeyInput();
	if (Player::GetInstance()->getjumpflag())
	{
		Player::GetInstance()->Jump();
	}
}

void GameManager::KeyInput()
{
	if (!m_bwinflag)
	{
		if (GetKeyState(VK_SPACE) & 0x8000)
		{

		}
		if (GetKeyState(VK_LEFT) & 0x8000)
		{
			if (m_imovemiter <= 0) m_imovemiter += MOVESPEED;
		}
		if (GetKeyState(VK_RIGHT) & 0x8000)
		{
			if (m_imovemiter >= -1800 * MOVESPEED) m_imovemiter -= MOVESPEED;
		}
		EnemyManager::GetInstance()->PointUpdate(m_imovemiter);
	}
}