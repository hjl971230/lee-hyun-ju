#include "Block.h"

Block::Block()
{
	m_iminecount = 0;
	m_bhideflag = true;
	m_buseflag = true;
}

Block::~Block()
{

}

void Block::Init(HDC hdc, HINSTANCE hInst)
{
	m_block.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\block.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_flag.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\flag.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	m_mine.Init(hdc, hInst, (HBITMAP)LoadImage(hInst, "BitMap\\mine.bmp", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	numbersload(hdc, hInst);
}

void Block::numbersload(HDC hdc, HINSTANCE hInst)
{
	TCHAR filenum[128] = "\0";
	for (int i = 0; i < BLOCK_COUNT; i++)
	{
		wsprintf(filenum, "BitMap\\block_%d.bmp", i);
		m_numbers[i].Init(hdc, hInst, (HBITMAP)LoadImage(hInst, filenum, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE | LR_LOADFROMFILE));
	}
}