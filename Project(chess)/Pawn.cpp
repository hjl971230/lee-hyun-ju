#include "ChessPiece.h"
Pawn::Pawn() { m_iNumCode = CHESSPIECE_NUM_PAWN; m_bfirstmoveflag = false; }
Pawn::Pawn(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_PAWN; m_bfirstmoveflag = false;}
Pawn::~Pawn() {}

void Pawn::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
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
	if (m_bfirstmoveflag)
	{
		if (m_chPlayerType == BLACK)
		{
			if (index_y + 1 < MAPSIZE_HEIGHT)
			{
				if (vec[index_y + 1][index_x] != NULL)
				{
					if (index_x < BMPSIZE_WIDTH - 1)
					{
						CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, true);
					}
					if (index_x > 0)
					{
						CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, true);
					}
				}
				else
				{
					CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
				}
			}
		}
		else
		{
			if (index_y - 1 >= 0)
			{
				if (vec[index_y - 1][index_x] != NULL)
				{
					CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y, true);
					CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y, true);
				}
				else
				{
					CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, true);
				}
			}
		}
	}
	else
	{
		if (m_chPlayerType == BLACK)
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y * 2, true);
		}
		else
		{
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, true);
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y * 2, true);
		}
	}
}

ChessPiece* Pawn::Move(HWND hWnd, vector<vector<ChessPiece*>> vec, int x, int y, bool& moveflag)
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
	
	if (m_bfirstmoveflag)
	{
		if (m_chPlayerType == BLACK)
		{
			if (index_y + 1 < MAPSIZE_HEIGHT)
			{
				if (vec[index_y + 1][index_x] != NULL)
				{
					if (index_x < BMPSIZE_WIDTH - 1)
					{
						//CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, true);
					}
					if (index_x > 0)
					{
						//CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, true);
					}
				}
				else
				{
					//CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
				}
			}
		}
		else
		{
			if (index_y - 1 >= 0)
			{
				if (vec[index_y - 1][index_x] != NULL)
				{
					//CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y, true);
					//CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y, true);
				}
				else
				{
					//CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, true);
				}
			}
		}
	}
	else
	{
		if (m_chPlayerType == BLACK)
		{
			if ((m_Point.x < x && x < m_Point.x + BMPSIZE_WIDTH / 2)
				&& (m_Point.y + size_y < y && y < m_Point.y + size_y + BMPSIZE_HEIGHT / 2))
			{
				m_Point.y = m_Point.y + size_y;
				tmp = vec[index_y + 1][index_x];
				vec[index_y + 1][index_x] = vec[index_y][index_x];
				vec[index_y][index_x] = NULL;
				moveflag = true;
				m_bfirstmoveflag = true;
			}
			else if ((m_Point.x < x && x < m_Point.x + size_x)
				&& (m_Point.y + size_y * 2 < y && y < m_Point.y + size_y * 2 + size_y))
			{
				m_Point.y = m_Point.y + size_y * 2;
				tmp = vec[index_y + 2][index_x];
				vec[index_y + 2][index_x] = vec[index_y][index_x];
				vec[index_y][index_x] = NULL;
				moveflag = true;
				m_bfirstmoveflag = true;
			}
			else moveflag = false;
		}
		else
		{
			if ((m_Point.x < x && x < m_Point.x + size_x)
				&& (m_Point.y - size_y < y && y < m_Point.y - size_y + size_y))
			{
				m_Point.y = m_Point.y - size_y;
				tmp = vec[index_y - 1][index_x];
				vec[index_y - 1][index_x] = vec[index_y][index_x];
				vec[index_y][index_x] = NULL;
				moveflag = true;
				m_bfirstmoveflag = true;
			}
			else if ((m_Point.x < x && x < m_Point.x + BMPSIZE_WIDTH / 2)
				&& (m_Point.y - size_y * 2 < y && y < m_Point.y - size_y * 2 + size_y))
			{
				m_Point.y = m_Point.y - size_y * 2;
				tmp = vec[index_y - 2][index_x];
				vec[index_y - 2][index_x] = vec[index_y][index_x];
				vec[index_y][index_x] = NULL;
				moveflag = true;
				m_bfirstmoveflag = true;
			}
			else moveflag = false;
		}
	}

	return tmp;
}