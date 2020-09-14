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
	winflag = false;
	m_iNormal_ver = BG_CODE_NORMAL;
}

GameManager::~GameManager()
{

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
	winflag = false;
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	m_BG[BG_CODE_BACK].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_DECO].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_deco.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_normal.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_BG[BG_CODE_NORMAL2].Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\back_normal2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	End.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\end.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Icon.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\icon.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_Miter.Init(m_BitMap.getMemDC(), hInst, (HBITMAP)LoadImage(hInst, "BitMap\\miter.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	Player::GetInstance()->Init(m_BitMap.getMemDC(), hInst);
}

void GameManager::GameDraw(HDC hdc, HINSTANCE hInst)
{
	m_BitMap.Init(hdc, hInst, CreateCompatibleBitmap(hdc, 2000, 1000));
	BGDraw(m_BitMap.getMemDC());
	End.Draw(m_BitMap.getMemDC(), ((m_BG[BG_CODE_BACK].getsize().cx) * 100) + m_imovemiter, 600);
	Player::GetInstance()->Draw(m_BitMap.getMemDC());
	BitBlt(hdc, 0, 0, m_BitMap.getsize().cx, m_BitMap.getsize().cy, m_BitMap.getMemDC(), 0, 0, SRCCOPY);
}

void GameManager::ScoreLifeDraw(HDC hdc)
{
	int score_x = 0;
	int life_x = 1500;
	int y = 60;
	TCHAR lifetext[128] = "Life";
	TCHAR scoretext[128] = "Score : ";
	wsprintf(scoretext, TEXT("Score : %d"), Player::GetInstance()->getscore());
	TextOut(hdc, score_x, y, scoretext, lstrlen(scoretext));
	TextOut(hdc, 1500 - lstrlen(lifetext), y / 2, lifetext, lstrlen(lifetext));
	for (int i = 0; i < Player::GetInstance()->getlife(); i++)
	{
		Icon.Draw(hdc, life_x, y, 2);
		life_x -= (Icon.getsize().cx + 50);
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
	int drawcount = 10;
	if (finishcheck())
	{
		winflag = true;
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
			PostQuitMessage(0);
		}
	}
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
	if (!winflag)
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
	}
}