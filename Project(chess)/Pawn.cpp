#include "ChessPiece.h"
Pawn::Pawn() { m_iNumCode = CHESSPIECE_NUM_PAWN; m_bfirstmoveflag = false; }
Pawn::Pawn(char ch) : ChessPiece(ch) { m_iNumCode = CHESSPIECE_NUM_PAWN; m_bfirstmoveflag = false;}
Pawn::~Pawn() {}

void Pawn::MoveCalculate(HWND hWnd, vector<vector<ChessPiece*>> vec)
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
	if (m_bfirstmoveflag)
	{
		if (m_chPlayerType == BLACK)
		{
			if (vec[y + 1][x] != NULL)
			{
				if (x < BMPSIZE_WIDTH - 1)
				{
					CalculateDraw(hWnd, m_szFileName, m_Point.x + size_x, m_Point.y + size_y, true);
				}
				if (x > 0)
				{
					CalculateDraw(hWnd, m_szFileName, m_Point.x - size_x, m_Point.y + size_y, true);
				}
			}
			else
			{
				CalculateDraw(hWnd, m_szFileName, m_Point.x, m_Point.y + size_y, true);
			}
		}
		else
		{
			if (vec[y - 1][x] != NULL)
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

ChessPiece* Pawn::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}