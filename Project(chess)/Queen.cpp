#include "ChessPiece.h"
Queen::Queen() { m_iNumCode = CHESSPIECE_NUM_QUEEN; }
Queen::Queen(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_QUEEN; }
Queen::~Queen() {}

void Queen::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
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

ChessPiece* Queen::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}