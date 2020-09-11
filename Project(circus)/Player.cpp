#include "Player.h"

Player* Player::m_this = NULL;

Player::Player()
{
	m_bjumpflag = false;
	m_ijump_x = 0;
	m_ijump_y = 0;
	m_ivelocity = JUMPSPEED * 2;
	m_point.x = 100;
	m_point.y = 600;
	m_imotion_num = PLAYER_MOTION_STAND;
	m_iwinmotion_num = 0;
}

Player::~Player()
{

}

void Player::Init(HDC hdc, HINSTANCE hInst)
{
	m_bjumpflag = false;
	m_ijump_x = 0;
	m_ijump_y = 0;
	m_ivelocity = JUMPSPEED * 2;
	m_point.x = 100;
	m_point.y = 600;
	m_imotion_num = PLAYER_MOTION_STAND;
	m_iwinmotion_num = 0;
	m_MotionBitMap[0].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\player0.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_MotionBitMap[1].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\player1.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_MotionBitMap[2].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\player2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_WinMotionBitMap[0].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\win.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_WinMotionBitMap[1].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\win2.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_DieBitMap.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\Player\\die.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void Player::Draw(HDC hdc)
{
	m_MotionBitMap[m_imotion_num].Draw(hdc, m_point.x, m_point.y + m_ijump_y);
}

void Player::WinDraw(HDC hdc)
{
	if (m_iwinmotion_num == 1) m_iwinmotion_num = 0;
	else m_iwinmotion_num = 1;
	m_WinMotionBitMap[m_iwinmotion_num].Draw(hdc, m_point.x, m_point.y + m_ijump_y);
}

void Player::DieDraw(HDC hdc)
{
	m_DieBitMap.Draw(hdc, m_point.x, m_point.y + m_ijump_y);
}

void Player::KeyInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_imotion_num = PLAYER_MOTION_JUMP;
		m_bjumpflag = true;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (!m_bjumpflag)
		{
			if (m_imotion_num != PLAYER_MOTION_BACK0)
				m_imotion_num = PLAYER_MOTION_BACK0;
			else m_imotion_num = PLAYER_MOTION_BACK1;
		}
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (!m_bjumpflag)
		{
			if (m_imotion_num != PLAYER_MOTION_RUN1)
				m_imotion_num = PLAYER_MOTION_RUN1;
			else m_imotion_num = PLAYER_MOTION_RUN2;
		}	
	}
}

void Player::Jump()
{
	if (m_ivelocity < -JUMPSPEED * 2)//일정량 상승하고 그만큼 내려오면 착지 했다는 것
	{
		m_ivelocity = JUMPSPEED * 2;//초기화 후 리턴
		m_bjumpflag = false;
		m_ijump_y = 0;
		m_imotion_num = PLAYER_MOTION_STAND;
		return;
	}
	m_ijump_y -= m_ivelocity;//점프할 크기를 속도만큼 빼고
	m_ivelocity -= GRAVITY;//속도는 중력에 영향을 받아 줄어든다
}