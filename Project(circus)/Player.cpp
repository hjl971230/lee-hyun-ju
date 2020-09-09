#include "Player.h"

Player* Player::m_this = NULL;

Player::Player()
{
	m_bjumpflag = false;
	m_ijump_x = 0;
	m_ijump_y = 0;
	m_ivelocity = MOVESPEED * 5;
	m_ix = 100;
	m_iy = 100;
}

Player::~Player()
{

}

//void Player::Init(HDC hdc, HINSTANCE hInst)
//{
//	MemDC[0] = CreateCompatibleDC(hdc);
//	m_pBitMap[0] = CreateCompatibleBitmap(hdc, 1300, 768);
//	m_pBitOld[0] = (HBITMAP)SelectObject(MemDC[0], m_pBitMap[0]);
//	MemDC[1] = CreateCompatibleDC(MemDC[0]);
//	m_pBitMap[1] = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
//	m_pBitOld[1] = (HBITMAP)SelectObject(MemDC[1], m_pBitMap[1]);
//	BITMAP BitMap_Info;
//	//준비된 비트맵의 정보를 가져온다. – width, height
//	GetObject(m_pBitMap[1], sizeof(BitMap_Info), &BitMap_Info);
//	m_size.cx = BitMap_Info.bmWidth;
//	m_size.cy = BitMap_Info.bmHeight;
//}
//
//void Player::Draw(HDC hdc)
//{
//	int tmp = m_isprite_sequence;
//	if (m_bjumpflag)
//	{
//		m_isprite_sequence = 1;
//		TransparentBlt(MemDC[0], m_ix + m_ijump_x, m_iy + m_ijump_y, (m_size.cx / 4), (m_size.cy / 4), MemDC[1],
//			(m_size.cx / 4) * m_isprite_sequence, (m_size.cy / 4) * view, (m_size.cx / 4), (m_size.cy / 4),
//			RGB(255, 0, 255));
//		m_isprite_sequence = tmp;
//	}
//	else
//	{
//		TransparentBlt(MemDC[0], m_ix + m_ijump_x, m_iy + m_ijump_y, (m_size.cx / 4), (m_size.cy / 4), MemDC[1],
//			(m_size.cx / 4) * m_isprite_sequence, (m_size.cy / 4) * view, (m_size.cx / 4), (m_size.cy / 4),
//			RGB(255, 0, 255));
//	}
//	BitBlt(hdc, 0, 0, 1300, 768, MemDC[0], 0, 0, SRCCOPY);
//}

void Player::KeyInput()
{
	if (GetKeyState(VK_SPACE) & 0x8000)
	{
		m_bjumpflag = true;
	}
	if (GetKeyState(VK_LEFT) & 0x8000)
	{
		if (m_ix + m_ijump_x - MOVESPEED >= 0)
			m_ix -= MOVESPEED;
	}
	if (GetKeyState(VK_RIGHT) & 0x8000)
	{
		if (m_ix + m_ijump_x + MOVESPEED <= 1300)
			m_ix += MOVESPEED;
	}
}

void Player::Jump()
{
	if (m_ivelocity < -MOVESPEED * 5)//일정량 상승하고 그만큼 내려오면 착지 했다는 것
	{
		m_ivelocity = MOVESPEED * 5;//초기화 후 리턴
		m_bjumpflag = false;
		m_ijump_y = 0;
		return;
	}
	m_ijump_y -= m_ivelocity;//점프할 크기를 속도만큼 빼고
	m_ivelocity -= GRAVITY;//속도는 중력에 영향을 받아 줄어든다
}