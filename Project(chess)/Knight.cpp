#include "ChessPiece.h"
Knight::Knight() { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::Knight(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::~Knight() {}


void Knight::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
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

	CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y, false);
	if (y - 1 >= 0)
	{
		if (x - 2 >= 0)
		{
			if (vec[y - 1][x - 2] != NULL && vec[y - 1][x - 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y - size_y, false);
			else if(vec[y - 1][x - 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y - size_y, true);
		}
		if (x + 2 < MAPSIZE_HEIGHT)
		{
			if (vec[y - 1][x + 2] != NULL && vec[y - 1][x + 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y - size_y, false);
			else if (vec[y - 1][x + 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y - size_y, true);
		}
	}

	if (y - 2 >= 0)
	{
		if (x - 1 >= 0)
		{
			if (vec[y - 2][x - 1] != NULL && vec[y - 2][x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y * 2, false);
			else if (vec[y - 2][x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y * 2, true);
		}
		if (x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[y - 2][x + 1] != NULL && vec[y - 2][x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y * 2, false);
			else if (vec[y - 2][x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y * 2, true);
		}
	}

	if (y + 1 < MAPSIZE_HEIGHT)
	{
		if (x - 2 >= 0)
		{
			if (vec[y + 1][x - 2] != NULL && vec[y + 1][x - 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y + size_y, false);
			else if (vec[y + 1][x - 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y + size_y, true);
		}
		if (x + 2 < MAPSIZE_WIDTH)
		{
			if (vec[y + 1][x + 2] != NULL && vec[y + 1][x + 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y + size_y, false);
			else if (vec[y + 1][x + 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y + size_y, true);
		}
	}

	if (y + 2 < MAPSIZE_HEIGHT)
	{
		if (x - 1 >= 0)
		{
			if (vec[y + 2][x - 1] != NULL && vec[y + 2][x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y * 2, false);
			else if (vec[y + 2][x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y * 2, true);
		}
		if (x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[y + 2][x + 1] != NULL && vec[y + 2][x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y * 2, false);
			else if (vec[y + 2][x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y * 2, true);
		}
	}
}

ChessPiece* Knight::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}