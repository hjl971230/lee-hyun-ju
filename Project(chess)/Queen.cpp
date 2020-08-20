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
}

ChessPiece* Queen::Move(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
	return NULL;
}