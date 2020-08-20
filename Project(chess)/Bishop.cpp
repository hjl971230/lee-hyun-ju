#include "ChessPiece.h"
Bishop::Bishop() { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::Bishop(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::~Bishop() {}

void Bishop::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)//대각선 전체 계산
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
	//CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y);
	//--,+-,-+,++
	for (int i = y, j = x; i >= 0 && j >= 0; i--, j--)
	{
		if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		add_x -= BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = y, j = x; i >= 0 && j < MAPSIZE_WIDTH; i--, j++)
	{
		if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		add_x += BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = y, j = x; i < MAPSIZE_HEIGHT && j >= 0; i++, j--)
	{
		if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		add_x -= BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = y, j = x; i < MAPSIZE_HEIGHT && j < MAPSIZE_WIDTH; i++, j++)
	{
		if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
			break;
		}
		CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		add_x += BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
}

ChessPiece* Bishop::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}