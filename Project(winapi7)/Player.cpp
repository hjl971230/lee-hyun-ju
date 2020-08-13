#include "Player.h"

Player* Player::m_this = NULL;

Player::Player()
{
	m_bjumpflag = false;
	m_ijump = 0;
	m_ivelocity = MOVESPEED * 10;
	view = VIEW_DOWN;
	m_ix = 100;
	m_iy = 100;
	m_isprite_sequence = 0;
}

Player::~Player()
{

}

void Player::Init(HWND hWnd, HINSTANCE hInst)
{
	HDC hdc = GetDC(hWnd);
	MemDC = CreateCompatibleDC(hdc);
	m_pBitMap = (HBITMAP)LoadImage(NULL, "image.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE);
	m_pBitOld = (HBITMAP)SelectObject(MemDC, m_pBitMap);
	BITMAP BitMap_Info;
	//준비된 비트맵의 정보를 가져온다. – width, height
	GetObject(m_pBitMap, sizeof(BitMap_Info), &BitMap_Info);
	m_size.cx = BitMap_Info.bmWidth;
	m_size.cy = BitMap_Info.bmHeight;
}

void Player::Draw(HDC hdc)
{
	int tmp = m_isprite_sequence;
	if (m_bjumpflag)
	{
		m_isprite_sequence = 1;
		TransparentBlt(hdc, m_ix, m_iy + m_ijump, (m_size.cx / 4), (m_size.cy / 4), MemDC,
			(m_size.cx / 4) * m_isprite_sequence, (m_size.cy / 4) * view, (m_size.cx / 4), (m_size.cy / 4),
			RGB(255, 0, 255));
		TransparentBlt(hdc, m_ix, m_iy + m_ijump, (m_size.cx / 4), (m_size.cy / 4), MemDC,
			0,0,0,0,
			RGB(255, 0, 255));
		m_isprite_sequence = tmp;
	}
	else TransparentBlt(hdc, m_ix, m_iy + m_ijump, (m_size.cx / 4), (m_size.cy / 4), MemDC,
		(m_size.cx / 4) * m_isprite_sequence, (m_size.cy / 4) * view, (m_size.cx / 4), (m_size.cy / 4),
		RGB(255, 0, 255));
	m_isprite_sequence = tmp;
}

void Player::Move(WPARAM wParam)
{
	switch (wParam)
	{
	case VK_LEFT:
		view = VIEW_LEFT;
		if (m_ix - MOVESPEED >= 0)
			m_ix -= MOVESPEED;
		break;
	case VK_RIGHT:
		view = VIEW_RIGHT;
		if (m_ix + MOVESPEED <= 1300)
			m_ix += MOVESPEED;
		break;
	case VK_UP:
		view = VIEW_UP;
		if (m_iy - MOVESPEED >= 0)
			m_iy -= MOVESPEED;
		break;
	case VK_DOWN:
		view = VIEW_DOWN;
		if (m_iy + MOVESPEED <= 600)
			m_iy += MOVESPEED;
		break;
	case VK_SPACE:
		m_bjumpflag = true;
		break;
	}
	if (wParam != VK_SPACE)
	{
		m_isprite_sequence++;
		if (m_isprite_sequence >= 4)
			m_isprite_sequence = 1;
	}
}

void Player::Jump()
{
	if (m_ivelocity < -MOVESPEED * 10)
	{
		m_ivelocity = MOVESPEED * 10;
		m_bjumpflag = false;
		m_ijump = 0;
		return;
	}
	m_ijump -= m_ivelocity;
	m_ivelocity -= GRAVITY;
}