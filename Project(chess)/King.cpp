#include "ChessPiece.h"
King::King() { m_iNumCode = CHESSPIECE_NUM_KING; }
King::King(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_KING; }
King::~King() {}

void King::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	BitMap* tmp = NULL;
	int size_x = BMPSIZE_WIDTH / 2;
	int size_y = BMPSIZE_HEIGHT / 2;
	int index_x = 0;
	int index_y = 0;
	for (int i = 0; i < MAPSIZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAPSIZE_WIDTH; j++)
		{
			if (vec[i][j] != NULL)
			{
				if (vec[i][j] == this)
				{
					index_y = i;
					index_x = j;
					break;
				}
			}
		}
	}

	CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y, false);
	if (index_y - 1 >= 0)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y - 1][index_x - 1] != NULL && vec[index_y - 1][index_x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y, false);
			else if (vec[index_y - 1][index_x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y, true);
		}
		if (index_x >= 0 && index_x < MAPSIZE_HEIGHT)
		{
			if (vec[index_y - 1][index_x] != NULL && vec[index_y - 1][index_x]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, false);
			else if (vec[index_y - 1][index_x] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, true);
		}
		if (index_x + 1 < MAPSIZE_HEIGHT)
		{
			if (vec[index_y - 1][index_x + 1] != NULL && vec[index_y - 1][index_x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y, false);
			else if (vec[index_y - 1][index_x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y, true);
		}
	}

	if (index_y >= 0 && index_y < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y][index_x - 1] != NULL && vec[index_y][index_x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y, false);
			else if (vec[index_y][index_x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y, true);
		}
		if (index_x + 1 < MAPSIZE_HEIGHT)
		{
			if (vec[index_y][index_x + 1] != NULL && vec[index_y][index_x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y, false);
			else if (vec[index_y][index_x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y, true);
		}
	}

	if (index_y + 1 < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y + 1][index_x - 1] != NULL && vec[index_y + 1][index_x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, false);
			else if (vec[index_y + 1][index_x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, true);
		}
		if (index_x >= 0 && index_x < MAPSIZE_HEIGHT)
		{
			if (vec[index_y + 1][index_x] != NULL && vec[index_y + 1][index_x]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, false);
			else if (vec[index_y + 1][index_x] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[index_y + 1][index_x + 1] != NULL && vec[index_y + 1][index_x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, false);
			else if (vec[index_y + 1][index_x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, true);
		}
	}
}

ChessPiece* King::Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag)
{
	ChessPiece* tmp = NULL;
	int size_x = BMPSIZE_WIDTH / 2;
	int size_y = BMPSIZE_HEIGHT / 2;
	int index_x = 0;
	int index_y = 0;
	for (int i = 0; i < MAPSIZE_HEIGHT; i++)
	{
		for (int j = 0; j < MAPSIZE_WIDTH; j++)
		{
			if (vec[i][j] != NULL)
			{
				if (vec[i][j] == this)
				{
					index_y = i;
					index_x = j;
					break;
				}
			}
		}
	}

	if (index_y - 1 >= 0)
	{
		if (index_x - 1 >= 0)
		{
			if ((vec[index_y - 1][index_x - 1] == NULL)
				|| vec[index_y - 1][index_x - 1] != NULL && vec[index_y - 1][index_x - 1]->getPlayerType() != m_chPlayerType)

			{
				if ((m_Point.x - size_x < x && x < m_Point.x - size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y < y && y < m_Point.y - size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x - size_x, m_Point.y - size_y, vec, index_x, index_y, index_x - 1, index_y - 1, moveflag);
				else moveflag = false;
			}
		}
		if (index_x >= 0 && index_x < MAPSIZE_HEIGHT)
		{
			if ((vec[index_y - 1][index_x] == NULL)
				|| vec[index_y - 1][index_x] != NULL && vec[index_y - 1][index_x]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x < x && x < m_Point.x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y < y && y < m_Point.y - size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x, m_Point.y - size_y, vec, index_x, index_y, index_x, index_y - 1, moveflag);
				else moveflag = false;
			}
		}
		if (index_x + 1 < MAPSIZE_HEIGHT)
		{
			if ((vec[index_y - 1][index_x + 1] == NULL)
				|| vec[index_y - 1][index_x + 1] != NULL && vec[index_y - 1][index_x + 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x < x && x < m_Point.x + size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y < y && y < m_Point.y - size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x + size_x, m_Point.y - size_y, vec, index_x, index_y, index_x + 1, index_y - 1, moveflag);
				else moveflag = false;
			}
		}
	}

	if (index_y >= 0 && index_y < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if ((vec[index_y][index_x - 1] == NULL)
				|| vec[index_y][index_x - 1] != NULL && vec[index_y][index_x - 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x < x && x < m_Point.x - size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y < y && y < m_Point.y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x - size_x, m_Point.y, vec, index_x, index_y, index_x - 1, index_y, moveflag);
				else moveflag = false;
			}
				
		}
		if (index_x + 1 < MAPSIZE_HEIGHT)
		{
			if ((vec[index_y][index_x + 1] == NULL)
				|| vec[index_y][index_x + 1] != NULL && vec[index_y][index_x + 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x < x && x < m_Point.x + size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y < y && y < m_Point.y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x + size_x, m_Point.y, vec, index_x, index_y, index_x + 1, index_y, moveflag);
				else moveflag = false;
			}
		}
	}

	if (index_y + 1 < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if ((vec[index_y + 1][index_x - 1] == NULL)
				|| vec[index_y + 1][index_x - 1] != NULL && vec[index_y + 1][index_x - 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x < x && x < m_Point.x - size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x - size_x, m_Point.y + size_y, vec, index_x, index_y, index_x - 1, index_y + 1, moveflag);
				else moveflag = false;
			}
		}
		if (index_x >= 0 && index_x < MAPSIZE_HEIGHT)
		{
			if ((vec[index_y + 1][index_x] == NULL)
				|| vec[index_y + 1][index_x] != NULL && vec[index_y + 1][index_x]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x < x && x < m_Point.x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x, m_Point.y + size_y, vec, index_x, index_y, index_x, index_y + 1, moveflag);
				else moveflag = false;
			}
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if ((vec[index_y + 1][index_x + 1] == NULL)
				|| vec[index_y + 1][index_x + 1] != NULL && vec[index_y + 1][index_x + 1]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, false);
				if ((m_Point.x + size_x < x && x < m_Point.x + size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
					return movefunc(m_Point.x + size_x, m_Point.y + size_y, vec, index_x, index_y, index_x + 1, index_y + 1, moveflag);
				else moveflag = false;
			}
		}
	}
	return NULL;
}

bool King::Check(HWND hWnd, vector<vector<ChessPiece*>>& vec)
{
	return false;
}