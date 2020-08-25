#include "ChessPiece.h"
Rook::Rook() { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::Rook(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_ROOK; }
Rook::~Rook() {}

void Rook::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)//가로/세로 끝까지 계산
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

	int add_x = 0;
	int add_y = 0;
	CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y, false);

	for (int i = index_y; i >= 0; i--)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, true);
		}
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y; i < MAPSIZE_HEIGHT; i++)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + add_y, true);
		}
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = index_x; j >= 0; j--)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, false);
				break;
			}
			else if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, true);
		}
		add_x -= BMPSIZE_WIDTH / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = index_x; j < MAPSIZE_WIDTH; j++)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, false);
				break;
			}
			else if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y, true);
		}
		add_x += BMPSIZE_WIDTH / 2;
	}
	add_x = 0;
	add_y = 0;
}

ChessPiece* Rook::Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag)
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

	int add_x = 0;
	int add_y = 0;

	for (int i = index_y; i >= 0; i--)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][index_x]->getPoint().x < x && x < vec[i][index_x]->getPoint().x + size_x)
					&& (vec[i][index_x]->getPoint().y < y && y < vec[i][index_x]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][index_x]->getPoint().x;
					m_Point.y = vec[i][index_x]->getPoint().y;
					tmp = vec[i][index_x];
					vec[i][index_x] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][index_x] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][index_x];
					vec[i][index_x] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y; i < MAPSIZE_HEIGHT; i++)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][index_x]->getPoint().x < x && x < vec[i][index_x]->getPoint().x + size_x)
					&& (vec[i][index_x]->getPoint().y < y && y < vec[i][index_x]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][index_x]->getPoint().x;
					m_Point.y = vec[i][index_x]->getPoint().y;
					tmp = vec[i][index_x];
					vec[i][index_x] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][index_x] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][index_x];
					vec[i][index_x] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = index_x; j >= 0; j--)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[index_y][j]->getPoint().x < x && x < vec[index_y][j]->getPoint().x + size_x)
					&& (vec[index_y][j]->getPoint().y < y && y < vec[index_y][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[index_y][j]->getPoint().x;
					m_Point.y = vec[index_y][j]->getPoint().y;
					tmp = vec[index_y][j];
					vec[index_y][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[index_y][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[index_y][j];
					vec[index_y][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_x -= BMPSIZE_WIDTH / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int j = index_x; j < MAPSIZE_WIDTH; j++)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[index_y][j]->getPoint().x < x && x < vec[index_y][j]->getPoint().x + size_x)
					&& (vec[index_y][j]->getPoint().y < y && y < vec[index_y][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[index_y][j]->getPoint().x;
					m_Point.y = vec[index_y][j]->getPoint().y;
					tmp = vec[index_y][j];
					vec[index_y][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[index_y][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[index_y][j];
					vec[index_y][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_x += BMPSIZE_WIDTH / 2;
	}
	return NULL;
}

void Rook::Check(HWND hWnd, vector<vector<ChessPiece*>>& vec)
{
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

	for (int i = index_y; i >= 0; i--)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType
				&& vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_KING)
			{
				vec[i][index_x]->setcheckedflag(true);
				break;
			}
			else if (vec[i][index_x] != NULL) break;
		}
	}
	for (int i = index_y; i < MAPSIZE_HEIGHT; i++)
	{
		if (i != index_y)
		{
			if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType
				&& vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_KING)
			{
				vec[i][index_x]->setcheckedflag(true);
				break;
			}
			else if (vec[i][index_x] != NULL) break;
		}
	}
	for (int j = index_x; j >= 0; j--)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType
				&& vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_KING)
			{
				vec[index_y][j]->setcheckedflag(true);
				break;
			}
			else if (vec[index_y][j] != NULL) break;
		}
	}
	for (int j = index_x; j < MAPSIZE_WIDTH; j++)
	{
		if (j != index_x)
		{
			if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType
				&& vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_KING)
			{
				vec[index_y][j]->setcheckedflag(true);
				break;
			}
			else if (vec[index_y][j] != NULL) break;
		}
	}
}