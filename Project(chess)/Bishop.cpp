#include "ChessPiece.h"
Bishop::Bishop() { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::Bishop(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_BISHOP; }
Bishop::~Bishop() {}

void Bishop::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)//대각선 전체 계산
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
	
	for (int i = index_y, j = index_x; i >= 0 && j >= 0; i--, j--)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		}
		add_x -= BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i >= 0 && j < MAPSIZE_WIDTH; i--, j++)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		}		
		add_x += BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j >= 0; i++, j--)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		}
		add_x -= BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j < MAPSIZE_WIDTH; i++, j++)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, false);
				break;
			}
			else if (vec[i][j] != NULL && vec[i][j]->getPlayerType() == m_chPlayerType) break;
			CalculateDraw(hWnd, m_szFileName, m_Point.x + add_x, m_Point.y + add_y, true);
		}
		add_x += BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
}

ChessPiece* Bishop::Move(HWND hWnd, vector<vector<ChessPiece*>>& vec, int x, int y, bool& moveflag)
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

	for (int i = index_y, j = index_x; i >= 0 && j >= 0; i--, j--)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][j]->getPoint().x < x && x < vec[i][j]->getPoint().x + size_x)
					&& (vec[i][j]->getPoint().y < y && y < vec[i][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][j]->getPoint().x;
					m_Point.y = vec[i][j]->getPoint().y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}

		}
		add_x -= BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i >= 0 && j < MAPSIZE_WIDTH; i--, j++)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][j]->getPoint().x < x && x < vec[i][j]->getPoint().x + size_x)
					&& (vec[i][j]->getPoint().y < y && y < vec[i][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][j]->getPoint().x;
					m_Point.y = vec[i][j]->getPoint().y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_x += BMPSIZE_WIDTH / 2;
		add_y -= BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j >= 0; i++, j--)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][j]->getPoint().x < x && x < vec[i][j]->getPoint().x + size_x)
					&& (vec[i][j]->getPoint().y < y && y < vec[i][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][j]->getPoint().x;
					m_Point.y = vec[i][j]->getPoint().y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_x -= BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
	add_x = 0;
	add_y = 0;
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j < MAPSIZE_WIDTH; i++, j++)
	{
		if (i != index_y && j != index_x)
		{
			if (vec[i][j] != NULL && vec[i][j]->getPlayerType() != m_chPlayerType)
			{
				if ((vec[i][j]->getPoint().x < x && x < vec[i][j]->getPoint().x + size_x)
					&& (vec[i][j]->getPoint().y < y && y < vec[i][j]->getPoint().y + size_y))
				{
					m_Point.x = vec[i][j]->getPoint().x;
					m_Point.y = vec[i][j]->getPoint().y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
				break;
			}
			else if (vec[i][j] == NULL)
			{
				if ((m_Point.x + add_x < x && x < m_Point.x + add_x + size_x)
					&& (m_Point.y + add_y < y && y < m_Point.y + add_y + size_y))
				{
					m_Point.x = m_Point.x + add_x;
					m_Point.y = m_Point.y + add_y;
					tmp = vec[i][j];
					vec[i][j] = vec[index_y][index_x];
					vec[index_y][index_x] = NULL;
					moveflag = true;
					return tmp;
				}
				else moveflag = false;
			}
		}
		add_x += BMPSIZE_WIDTH / 2;
		add_y += BMPSIZE_HEIGHT / 2;
	}
	return NULL;
}