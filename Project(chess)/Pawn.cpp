#include "ChessPiece.h"
Pawn::Pawn() { m_iNumCode = CHESSPIECE_NUM_PAWN; }
Pawn::Pawn(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_PAWN; }
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
	
	if (m_chPlayerType == BLACK)
	{
		if (index_y + 1 <= MAPSIZE_HEIGHT - 1)
		{
			if (vec[index_y + 1][index_x] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
			if (!m_bfirstmoveflag)
			{
				if (vec[index_y + 1][index_x] == NULL)
				{
					if (vec[index_y + 2][index_x] == NULL)
						CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y * 2, true);
				}
			}
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y + 1][index_x + 1] != NULL)
					{
						if (vec[index_y + 1][index_x + 1]->getPlayerType() != m_chPlayerType)
							CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, false);
					}
				}
			}
			if (index_x >= 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y + 1][index_x - 1] != NULL)
					{
						if (vec[index_y + 1][index_x - 1]->getPlayerType() != m_chPlayerType)
							CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, false);
					}
				}
			}
		}
	}
	else
	{
		if (index_y - 1 >= 0)
		{
			if (vec[index_y - 1][index_x] == NULL)
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y, true);
			if (!m_bfirstmoveflag)
			{
				if (vec[index_y - 1][index_x] == NULL)
				{
					if (vec[index_y - 2][index_x] == NULL)
						CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y - size_y * 2, true);
				}
			}
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y - 1][index_x + 1] != NULL)
					{
						if (vec[index_y - 1][index_x + 1]->getPlayerType() != m_chPlayerType)
							CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y - size_y, false);
					}
				}
			}
			if (index_x > 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y - 1][index_x - 1] != NULL)
					{
						if (vec[index_y - 1][index_x - 1]->getPlayerType() != m_chPlayerType)
							CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y - size_y, false);
					}
				}
			}
		}
	}
}

ChessPiece* Pawn::Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag)
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

	if (m_chPlayerType == BLACK)
	{
		if (index_y + 1 <= MAPSIZE_HEIGHT - 1)
		{
			if (vec[index_y + 1][index_x] == NULL)
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
					return tmp;
				}
				else moveflag = false;
			}
			if (!m_bfirstmoveflag)
			{
				if (vec[index_y + 1][index_x] == NULL)
				{
					if (vec[index_y + 2][index_x] == NULL)
					{
						if ((m_Point.x < x && x < m_Point.x + size_x)
							&& (m_Point.y + size_y * 2 < y && y < m_Point.y + size_y * 2 + size_y))
						{
							m_Point.y = m_Point.y + size_y * 2;
							tmp = vec[index_y + 2][index_x];
							vec[index_y + 2][index_x] = vec[index_y][index_x];
							vec[index_y][index_x] = NULL;
							moveflag = true;
							m_bfirstmoveflag = true;
							return tmp;
						}
						else moveflag = false;
					}
				}
			}
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y + 1][index_x + 1] != NULL)
					{
						if (vec[index_y + 1][index_x + 1]->getPlayerType() != m_chPlayerType)
						{
							if ((m_Point.x + size_x < x && x < m_Point.x + size_x + size_x)
								&& (m_Point.y + size_y < y && y < m_Point.y + size_y + size_y))
							{
								m_Point.x = m_Point.x + size_x;
								m_Point.y = m_Point.y + size_y;
								tmp = vec[index_y + 1][index_x + 1];
								vec[index_y + 1][index_x + 1] = vec[index_y][index_x];
								vec[index_y][index_x] = NULL;
								moveflag = true;
								m_bfirstmoveflag = true;
								return tmp;
							}
							else moveflag = false;
						}
					}
				}
			}
			if (index_x >= 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y + 1][index_x - 1] != NULL)
					{
						if (vec[index_y + 1][index_x - 1]->getPlayerType() != m_chPlayerType)
						{
							if ((m_Point.x - size_x < x && x < m_Point.x - size_x + size_x)
								&& (m_Point.y + size_y < y && y < m_Point.y + size_y + size_y))
							{
								m_Point.x = m_Point.x - size_x;
								m_Point.y = m_Point.y + size_y;
								tmp = vec[index_y + 1][index_x - 1];
								vec[index_y + 1][index_x - 1] = vec[index_y][index_x];
								vec[index_y][index_x] = NULL;
								moveflag = true;
								m_bfirstmoveflag = true;
								return tmp;
							}
							else moveflag = false;
						}
					}
				}
			}
		}
	}
	else
	{
		if (index_y - 1 >= 0)
		{
			if (vec[index_y - 1][index_x] == NULL)
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
					return tmp;
				}
				else moveflag = false;
			}
			if (!m_bfirstmoveflag)
			{
				if (vec[index_y - 1][index_x] == NULL)
				{
					if (vec[index_y - 2][index_x] == NULL)
					{
						if ((m_Point.x < x && x < m_Point.x + BMPSIZE_WIDTH / 2)
							&& (m_Point.y - size_y * 2 < y && y < m_Point.y - size_y * 2 + size_y))
						{
							m_Point.y = m_Point.y - size_y * 2;
							tmp = vec[index_y - 2][index_x];
							vec[index_y - 2][index_x] = vec[index_y][index_x];
							vec[index_y][index_x] = NULL;
							moveflag = true;
							m_bfirstmoveflag = true;
							return tmp;
						}
						else moveflag = false;
					}
				}
			}
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y - 1][index_x + 1] != NULL)
					{
						if (vec[index_y - 1][index_x + 1]->getPlayerType() != m_chPlayerType)
						{
							if ((m_Point.x + size_x < x && x < m_Point.x + size_x + size_x)
								&& (m_Point.y - size_y < y && y < m_Point.y - size_y + size_y))
							{
								m_Point.x = m_Point.x + size_x;
								m_Point.y = m_Point.y - size_y;
								tmp = vec[index_y - 1][index_x + 1];
								vec[index_y - 1][index_x + 1] = vec[index_y][index_x];
								vec[index_y][index_x] = NULL;
								moveflag = true;
								m_bfirstmoveflag = true;
								return tmp;
							}
							else moveflag = false;
						}
					}
				}
			}
			if (index_x > 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y - 1][index_x - 1] != NULL)
					{
						if (vec[index_y - 1][index_x - 1]->getPlayerType() != m_chPlayerType)
						{
							if ((m_Point.x - size_x < x && x < m_Point.x - size_x + size_x)
								&& (m_Point.y - size_y < y && y < m_Point.y - size_y + size_y))
							{
								m_Point.x = m_Point.x - size_x;
								m_Point.y = m_Point.y - size_y;
								tmp = vec[index_y - 1][index_x - 1];
								vec[index_y - 1][index_x - 1] = vec[index_y][index_x];
								vec[index_y][index_x] = NULL;
								moveflag = true;
								m_bfirstmoveflag = true;
								return tmp;
							}
							else moveflag = false;
						}
					}
				}
			}
		}
	}

	return tmp;
}

void Pawn::Check(HWND hWnd, vector<vector<ChessPiece*>>& vec)
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

	if (m_chPlayerType == BLACK)
	{
		if (index_y + 1 <= MAPSIZE_HEIGHT - 1)
		{
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y + 1][index_x + 1] != NULL)
					{
						if (vec[index_y + 1][index_x + 1]->getPlayerType() != m_chPlayerType
							&& vec[index_y + 1][index_x + 1]->getNumCode() == CHESSPIECE_NUM_KING)
						{
							vec[index_y + 1][index_x + 1]->setcheckedflag(true);
							return;
						}
					}
				}
			}
			if (index_x >= 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y + 1][index_x - 1] != NULL)
					{
						if (vec[index_y + 1][index_x - 1]->getPlayerType() != m_chPlayerType
							&& vec[index_y + 1][index_x - 1]->getNumCode() == CHESSPIECE_NUM_KING)
						{
							vec[index_y + 1][index_x - 1]->setcheckedflag(true);
							return;
						}
					}
				}
			}
		}
	}
	else
	{
		if (index_y - 1 >= 0)
		{
			if (index_x <= MAPSIZE_WIDTH - 1)
			{
				if (index_x + 1 <= MAPSIZE_WIDTH - 1)
				{
					if (vec[index_y - 1][index_x + 1] != NULL)
					{
						if (vec[index_y - 1][index_x + 1]->getPlayerType() != m_chPlayerType
							&& vec[index_y - 1][index_x + 1]->getNumCode() == CHESSPIECE_NUM_KING)
						{
							vec[index_y - 1][index_x + 1]->setcheckedflag(true);
							return;
						}
					}
				}
			}
			if (index_x > 0)
			{
				if (index_x - 1 >= 0)
				{
					if (vec[index_y - 1][index_x - 1] != NULL)
					{
						if (vec[index_y - 1][index_x - 1]->getPlayerType() != m_chPlayerType
							&& vec[index_y - 1][index_x - 1]->getNumCode() == CHESSPIECE_NUM_KING)
						{
							vec[index_y - 1][index_x - 1]->setcheckedflag(true);
							return;
						}
					}
				}
			}
		}
	}
}