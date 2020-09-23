#include "Block.h"

Block::Block()
{
	m_iminecount = 0;
	m_ihideflag = MINE_HIDE;
}

Block::~Block()
{

}

void Block::Init(HDC hdc, HINSTANCE hInst)
{
	m_block.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\block.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_flag.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\flag.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_mine.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\mine.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	//numbersload(hdc, hInst);
}

void Block::numbersload(HDC hdc, HINSTANCE hInst)
{
	TCHAR filenum[128] = "\0";
	wsprintf(filenum, "BitMap\\block_%d.bmp", m_iminecount);
	m_numbers.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, filenum, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
}

void Block::Draw(HDC hdc, int x, int y, float scale_x, float scale_y)
{
	if (m_ihideflag == MINE_HIDE)
		m_block.Draw(hdc, x, y);
	else if (m_ihideflag == MINE_FLAG) m_flag.Draw(hdc, x, y);
	else m_numbers.Draw(hdc, x, y);
}