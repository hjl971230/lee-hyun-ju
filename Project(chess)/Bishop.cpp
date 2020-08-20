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

	//CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y);
	int i = y;
	int j = x;
	
}