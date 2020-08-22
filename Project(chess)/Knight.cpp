#include "ChessPiece.h"
Knight::Knight() { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::Knight(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_KNIGHT; }
Knight::~Knight() {}

void Knight::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
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
		if (index_x - 2 >= 0)
		{
			if (vec[index_y - 1][index_x - 2] != NULL && vec[index_y - 1][index_x - 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y - size_y, false);
			else if(vec[index_y - 1][index_x - 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y - size_y, true);
		}
		if (index_x + 2 < MAPSIZE_HEIGHT)
		{
			if (vec[index_y - 1][index_x + 2] != NULL && vec[index_y - 1][index_x + 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y - size_y, false);
			else if (vec[index_y - 1][index_x + 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y - size_y, true);
		}
	}

	if (index_y - 2 >= 0)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y - 2][index_x - 1] != NULL && vec[index_y - 2][index_x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y * 2, false);
			else if (vec[index_y - 2][index_x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y * 2, true);
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[index_y - 2][index_x + 1] != NULL && vec[index_y - 2][index_x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y * 2, false);
			else if (vec[index_y - 2][index_x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y * 2, true);
		}
	}

	if (index_y + 1 < MAPSIZE_HEIGHT)
	{
		if (index_x - 2 >= 0)
		{
			if (vec[index_y + 1][index_x - 2] != NULL && vec[index_y + 1][index_x - 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y + size_y, false);
			else if (vec[index_y + 1][index_x - 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x * 2, m_Point.y + size_y, true);
		}
		if (index_x + 2 < MAPSIZE_WIDTH)
		{
			if (vec[index_y + 1][index_x + 2] != NULL && vec[index_y + 1][index_x + 2]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y + size_y, false);
			else if (vec[index_y + 1][index_x + 2] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x * 2, m_Point.y + size_y, true);
		}
	}

	if (index_y + 2 < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y + 2][index_x - 1] != NULL && vec[index_y + 2][index_x - 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y * 2, false);
			else if (vec[index_y + 2][index_x - 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y * 2, true);
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[index_y + 2][index_x + 1] != NULL && vec[index_y + 2][index_x + 1]->getPlayerType() != m_chPlayerType)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y * 2, false);
			else if (vec[index_y + 2][index_x + 1] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y * 2, true);
		}
	}
}

ChessPiece* Knight::Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag)
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

	CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y, false);
	if (index_y - 1 >= 0)
	{
		if (index_x - 2 >= 0)
		{
			if ((vec[index_y - 1][index_x - 2] == NULL) || 
				vec[index_y - 1][index_x - 2] != NULL && vec[index_y - 1][index_x - 2]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x * 2 < x && x < m_Point.x - size_x * 2 + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y < y && y < m_Point.y - size_y + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x - size_x * 2;
					m_Point.y = m_Point.y - size_y;
					tmp = vec[index_y - 1][index_x - 2];
					vec[index_y - 1][index_x - 2] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		if (index_x + 2 < MAPSIZE_HEIGHT)
		{
			if ((vec[index_y - 1][index_x + 2] == NULL)
				|| vec[index_y - 1][index_x + 2] != NULL && vec[index_y - 1][index_x + 2]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x * 2 < x && x < m_Point.x + size_x * 2 + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y < y && y < m_Point.y - size_y + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x + size_x * 2;
					m_Point.y = m_Point.y - size_y;
					tmp = vec[index_y - 1][index_x + 2];
					vec[index_y - 1][index_x + 2] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
	}

	if (index_y - 2 >= 0)
	{
		if (index_x - 1 >= 0)
		{
			if ((vec[index_y - 2][index_x - 1] == NULL) 
				|| vec[index_y - 2][index_x - 1] != NULL && vec[index_y - 2][index_x - 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x < x && x < m_Point.x - size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y * 2 < y && y < m_Point.y - size_y * 2 + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x - size_x;
					m_Point.y = m_Point.y - size_y * 2;
					tmp = vec[index_y - 2][index_x - 1];
					vec[index_y - 2][index_x - 1] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if ((vec[index_y - 2][index_x + 1] == NULL)
				|| vec[index_y - 2][index_x + 1] != NULL && vec[index_y - 2][index_x + 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x < x && x < m_Point.x + size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y - size_y * 2 < y && y < m_Point.y - size_y * 2 + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x + size_x;
					m_Point.y = m_Point.y - size_y * 2;
					tmp = vec[index_y - 2][index_x + 1];
					vec[index_y - 2][index_x + 1] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
	}

	if (index_y + 1 < MAPSIZE_HEIGHT)
	{
		if (index_x - 2 >= 0)
		{
			if ((vec[index_y + 1][index_x - 2] == NULL)
				|| vec[index_y + 1][index_x - 2] != NULL && vec[index_y + 1][index_x - 2]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x * 2 < x && x < m_Point.x - size_x * 2 + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x - size_x * 2;
					m_Point.y = m_Point.y + size_y;
					tmp = vec[index_y + 1][index_x - 2];
					vec[index_y + 1][index_x - 2] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		if (index_x + 2 < MAPSIZE_WIDTH)
		{
			if ((vec[index_y + 1][index_x + 2] == NULL)
				|| vec[index_y + 1][index_x + 2] != NULL && vec[index_y + 1][index_x + 2]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x * 2 < x && x < m_Point.x + size_x * 2 + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x + size_x * 2;
					m_Point.y = m_Point.y + size_y;
					tmp = vec[index_y + 1][index_x + 2];
					vec[index_y + 1][index_x + 2] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
	}

	if (index_y + 2 < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if ((vec[index_y + 2][index_x - 1] == NULL)
				|| vec[index_y + 2][index_x - 1] != NULL && vec[index_y + 2][index_x - 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x - size_x < x && x < m_Point.x - size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y * 2 < y && y < m_Point.y + size_y * 2 + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x - size_x;
					m_Point.y = m_Point.y + size_y * 2;
					tmp = vec[index_y + 2][index_x - 1];
					vec[index_y + 2][index_x - 1] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if ((vec[index_y + 2][index_x + 1] == NULL)
				|| vec[index_y + 2][index_x + 1] != NULL && vec[index_y + 2][index_x + 1]->getPlayerType() != m_chPlayerType)
			{
				if ((m_Point.x + size_x < x && x < m_Point.x + size_x + BMPSIZE_WIDTH / 2)
					&& (m_Point.y + size_y * 2 < y && y < m_Point.y + size_y * 2 + BMPSIZE_HEIGHT / 2))
				{
					m_Point.x = m_Point.x + size_x;
					m_Point.y = m_Point.y + size_y * 2;
					tmp = vec[index_y + 2][index_x + 1];
					vec[index_y + 2][index_x + 1] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
	}
	return NULL;
}