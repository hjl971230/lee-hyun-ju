#include "ChessPiece.h"
Rook::Rook() { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::Rook(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::~Rook() {}

void Rook::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)//가로/세로 끝까지 계산
{
	BitMap* tmp = NULL;
	int size_x = BMPSIZE_WIDTH / 2;
	int size_y = BMPSIZE_HEIGHT / 2;
	int x = 0;
	int y = 0;
	for (int i = 0; i < MAPSIZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAPSIZE_WIDTH; j++)
		{
			if (vec[i][j] != NULL)
			{
				if (vec[i][j] == this)
				{
					y = i;
					x = j;
					break;
				}
			}
		}
	}

	int add_x = 0;
	int add_y = 0;
	for (int i = y; i >= 0; i--)
	{
		if (vec[i][x] != NULL && vec[i][x]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, true);
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = y + 1; i < MAPSIZE_HEIGHT; i++)
	{
		if (vec[i][x] != NULL && vec[i][x]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, true);
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = x; j >= 0; j--)
	{
		if (vec[y][j] != NULL && vec[y][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, true);
		add_x -= BMPSIZE_WIDTH / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = x + 1; j < MAPSIZE_WIDTH; j++)
	{
		if (vec[y][j] != NULL && vec[y][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, true);
		add_x += BMPSIZE_WIDTH / 2;
	}
	add_x = 0;
	add_y = 0;
}

ChessPiece* Rook::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}