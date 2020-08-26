#include "ChessPiece.h"

ChessPiece::ChessPiece() 
{ 
	m_bClickflag = false; 
	m_bfirstmoveflag = false; 
	m_bPromotionflag = false; 
	m_bcheckedflag = false;
}
ChessPiece::ChessPiece(char ch) : m_chPlayerType(ch) 
{ 
	m_bClickflag = false; 
	m_bfirstmoveflag = false; 
	m_bPromotionflag = false;
	m_bcheckedflag = false;
}
ChessPiece::~ChessPiece(){}

void ChessPiece::FileNameSetting()
{
	sprintf(m_szFileName, "block_%c_0%d.bmp", m_chPlayerType, m_iNumCode);
}

void ChessPiece::CalculateDraw(HWND hWnd, TCHAR FileName[128], int x, int y, bool flag)
{
	BitMap* tmp = NULL;
	tmp = new BitMap;
	tmp->setFileName(FileName);
	tmp->Init(hWnd, x, y);
	if(flag) 
		tmp->Draw(GetDC(hWnd));
	else
	{
		if(m_chPlayerType == BLACK) tmp->colorDraw(GetDC(hWnd), 255, 255, 255);
		else tmp->colorDraw(GetDC(hWnd), 0, 0, 0);
	}
		
	delete tmp;
}

ChessPiece* ChessPiece::movefunc(int change_x, int change_y,
	vector<vector<ChessPiece*>>& vec, int index_x, int index_y, int change_index_x, int change_index_y, bool& flag)
{
	ChessPiece* tmp = NULL;
	vec[index_y][index_x]->setPoint(change_x, change_y);
	tmp = vec[change_index_y][change_index_x];
	vec[change_index_y][change_index_x] = vec[index_y][index_x];
	vec[index_y][index_x] = NULL;
	flag = true;
	return tmp;
}

int ChessPiece::Promotion(HWND hWnd, vector<vector<ChessPiece*>> vec)
{
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
	if ((m_chPlayerType == WHITE && index_y == 0) || (m_chPlayerType == BLACK && index_y == MAPSIZE_HEIGHT - 1))
	{
		m_bPromotionflag = true;
		if (MessageBox(hWnd, TEXT("퀸으로 프로모션 하시겠습니까?"), TEXT("Promotion Queen"), MB_YESNO) == IDYES)
		{
			m_bPromotionflag = true;
			return CHESSPIECE_NUM_QUEEN;
		}
		else
		{
			if (MessageBox(hWnd, TEXT("룩으로 프로모션 하시겠습니까?"), TEXT("Promotion Rook"), MB_YESNO) == IDYES)
			{
				m_bPromotionflag = true;
				return CHESSPIECE_NUM_ROOK;
			}
			else
			{
				if (MessageBox(hWnd, TEXT("비숍으로 프로모션 하시겠습니까?"), TEXT("Promotion Bishop"), MB_YESNO) == IDYES)
				{
					m_bPromotionflag = true;
					return CHESSPIECE_NUM_BISHOP;
				}
				else
				{
					if (MessageBox(hWnd, TEXT("나이트으로 프로모션 하시겠습니까?"), TEXT("Promotion Knight"), MB_YESNO) == IDYES)
					{
						m_bPromotionflag = true;
						return CHESSPIECE_NUM_KNIGHT;
					}
					else
					{
						m_bPromotionflag = false;
						return CHESSPIECE_NUM_PAWN;
					}
				}
			}
		}
	}
	m_bPromotionflag = false;
	return CHESSPIECE_NUM_PAWN;
}

bool ChessPiece::CheckMatecheck(vector<vector<ChessPiece*>> vec)
{
	vector<bool> checkflag;
	checkflag.reserve(9);
	checkflag.assign(9, false);
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

	if (m_iNumCode == CHESSPIECE_NUM_KING && m_bcheckedflag)
	{
		if (index_y - 1 >= 0 && index_y - 1 < MAPSIZE_HEIGHT)
		{
			if (index_x - 1 >= 0 && index_x - 1 < MAPSIZE_WIDTH && vec[index_y - 1][index_x - 1] == NULL)
			{
				if (RookCheck(vec, index_x - 1, index_y - 1)
					|| BishopCheck(vec, index_x - 1, index_y - 1)
					|| KnightCheck(vec, index_x - 1, index_y - 1)
					|| PawnCheck(vec, index_x - 1, index_y - 1)) checkflag[0] = true;
				else
					checkflag[0] = false;
			}
			else
				checkflag[0] = true;
			if (index_x >= 0 && index_x < MAPSIZE_WIDTH && vec[index_y - 1][index_x] == NULL)
			{
				if (RookCheck(vec, index_x, index_y - 1)
					|| BishopCheck(vec, index_x, index_y - 1)
					|| KnightCheck(vec, index_x, index_y - 1)
					|| PawnCheck(vec, index_x, index_y - 1)) checkflag[1] = true;
				else
					checkflag[1] = false;
			}
			else
				checkflag[1] = true;
			if (index_x + 1 >= 0 && index_x + 1 < MAPSIZE_WIDTH && vec[index_y - 1][index_x + 1] == NULL)
			{
				if (RookCheck(vec, index_x + 1, index_y - 1)
					|| BishopCheck(vec, index_x + 1, index_y - 1)
					|| KnightCheck(vec, index_x + 1, index_y - 1)
					|| PawnCheck(vec, index_x + 1, index_y - 1)) checkflag[2] = true;
				else
					checkflag[2] = false;
			}
			else
				checkflag[2] = true;
		}
		else
		{
			checkflag[0] = true;
			checkflag[1] = true;
			checkflag[2] = true;
		}
		if (index_y >= 0 && index_y < MAPSIZE_HEIGHT)
		{
			if (index_x - 1 >= 0 && index_x - 1 < MAPSIZE_WIDTH && vec[index_y][index_x - 1] == NULL)
			{
				if (RookCheck(vec, index_x - 1, index_y)
					|| BishopCheck(vec, index_x - 1, index_y)
					|| KnightCheck(vec, index_x - 1, index_y)
					|| PawnCheck(vec, index_x - 1, index_y)) checkflag[3] = true;
				else
					checkflag[3] = false;
			}
			else
				checkflag[3] = true;
			if (index_x >= 0 && index_x < MAPSIZE_WIDTH && vec[index_y][index_x] == NULL)
			{
				if (RookCheck(vec, index_x, index_y)
					|| BishopCheck(vec, index_x, index_y)
					|| KnightCheck(vec, index_x, index_y)
					|| PawnCheck(vec, index_x, index_y)) checkflag[4] = true;
				else
					checkflag[4] = false;
			}
			else
				checkflag[4] = true;
			if (index_x + 1 >= 0 && index_x + 1 < MAPSIZE_WIDTH && vec[index_y][index_x + 1] == NULL)
			{
				if (RookCheck(vec, index_x + 1, index_y)
					|| BishopCheck(vec, index_x + 1, index_y)
					|| KnightCheck(vec, index_x + 1, index_y)
					|| PawnCheck(vec, index_x + 1, index_y)) checkflag[5] = true;
				else
					checkflag[5] = false;
			}
			else
				checkflag[5] = true;
		}
		else
		{
			checkflag[3] = true;
			checkflag[4] = true;
			checkflag[5] = true;
		}
		if (index_y + 1 >= 0 && index_y + 1 < MAPSIZE_HEIGHT)
		{
			if (index_x - 1 >= 0 && index_x - 1 < MAPSIZE_WIDTH && vec[index_y + 1][index_x - 1] == NULL)
			{
				if (RookCheck(vec, index_x - 1, index_y + 1)
					|| BishopCheck(vec, index_x - 1, index_y + 1)
					|| KnightCheck(vec, index_x - 1, index_y + 1)
					|| PawnCheck(vec, index_x - 1, index_y + 1)) checkflag[6] = true;
				else
					checkflag[6] = false;
			}
			else
				checkflag[6] = true;
			if (index_x >= 0 && index_x < MAPSIZE_WIDTH && vec[index_y + 1][index_x] == NULL)
			{
				if (RookCheck(vec, index_x, index_y + 1)
					|| BishopCheck(vec, index_x, index_y + 1)
					|| KnightCheck(vec, index_x, index_y + 1)
					|| PawnCheck(vec, index_x, index_y + 1)) checkflag[7] = true;
				else
					checkflag[7] = false;
			}
			else
				checkflag[7] = true;
			if (index_x + 1 >= 0 && index_x + 1 < MAPSIZE_WIDTH && vec[index_y + 1][index_x + 1] == NULL)
			{
				if (RookCheck(vec, index_x + 1, index_y + 1)
					|| BishopCheck(vec, index_x + 1, index_y + 1)
					|| KnightCheck(vec, index_x + 1, index_y + 1)
					|| PawnCheck(vec, index_x + 1, index_y + 1)) checkflag[8] = true;
				else
					checkflag[8] = false;
			}
			else
				checkflag[8] = true;
		}
		else
		{
			checkflag[6] = true;
			checkflag[7] = true;
			checkflag[8] = true;
		}
	}

	for (vector<bool>::iterator iter = checkflag.begin(); iter != checkflag.end(); iter++)
	{
		if (!(*iter)) return false;
	}
	return true;
}

bool ChessPiece::RookCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y)
{
	for (int i = index_y; i >= 0; i--)
	{
		if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType
			&& (vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_ROOK || vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[i][index_x] != NULL)break;
	}
	for (int i = index_y; i < MAPSIZE_HEIGHT; i++)
	{
		if (vec[i][index_x] != NULL && vec[i][index_x]->getPlayerType() != m_chPlayerType
			&& (vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_ROOK || vec[i][index_x]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[i][index_x] != NULL)break;
	}
	for (int j = index_x; j >= 0; j--)
	{
		if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType
			&& (vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_ROOK || vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[index_y][j] != NULL)break;
	}
	for (int j = index_x; j < MAPSIZE_WIDTH; j++)
	{
		if (vec[index_y][j] != NULL && vec[index_y][j]->getPlayerType() != m_chPlayerType
			&& (vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_ROOK || vec[index_y][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[index_y][j] != NULL)break;
	}
	return false;
}

bool ChessPiece::BishopCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y)
{
	for (int i = index_y, j = index_x; i >= 0 && j >= 0; i--, j--)
	{
		if (vec[i][j] != NULL
			&& vec[i][j]->getPlayerType() != m_chPlayerType
			&& (vec[i][j]->getNumCode() == CHESSPIECE_NUM_BISHOP || vec[i][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if(vec[i][j] != NULL)break;
	}
	for (int i = index_y, j = index_x; i >= 0 && j < MAPSIZE_WIDTH; i--, j++)
	{
		if (vec[i][j] != NULL
			&& vec[i][j]->getPlayerType() != m_chPlayerType
			&& (vec[i][j]->getNumCode() == CHESSPIECE_NUM_BISHOP || vec[i][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[i][j] != NULL)break;
	}
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j >= 0; i++, j--)
	{
		if (vec[i][j] != NULL
			&& vec[i][j]->getPlayerType() != m_chPlayerType
			&& (vec[i][j]->getNumCode() == CHESSPIECE_NUM_BISHOP || vec[i][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[i][j] != NULL)break;
	}
	for (int i = index_y, j = index_x; i < MAPSIZE_HEIGHT && j < MAPSIZE_WIDTH; i++, j++)
	{
		if (vec[i][j] != NULL
			&& vec[i][j]->getPlayerType() != m_chPlayerType
			&& (vec[i][j]->getNumCode() == CHESSPIECE_NUM_BISHOP || vec[i][j]->getNumCode() == CHESSPIECE_NUM_QUEEN))
			return true;
		else if (vec[i][j] != NULL)break;
	}

	return false;
}

bool ChessPiece::KnightCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y)
{
	if (index_y - 1 >= 0)
	{
		if (index_x - 2 >= 0)
		{
			if (vec[index_y - 1][index_x - 2] != NULL && vec[index_y - 1][index_x - 2]->getPlayerType() != m_chPlayerType
				&& vec[index_y - 1][index_x - 2]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
		if (index_x + 2 < MAPSIZE_HEIGHT)
		{
			if (vec[index_y - 1][index_x + 2] != NULL && vec[index_y - 1][index_x + 2]->getPlayerType() != m_chPlayerType
				&& vec[index_y - 1][index_x + 2]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
	}

	if (index_y - 2 >= 0)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y - 2][index_x - 1] != NULL && vec[index_y - 2][index_x - 1]->getPlayerType() != m_chPlayerType
				&& vec[index_y - 2][index_x - 1]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[index_y - 2][index_x + 1] != NULL && vec[index_y - 2][index_x + 1]->getPlayerType() != m_chPlayerType
				&& vec[index_y - 2][index_x + 1]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
	}

	if (index_y + 1 < MAPSIZE_HEIGHT)
	{
		if (index_x - 2 >= 0)
		{
			if (vec[index_y + 1][index_x - 2] != NULL && vec[index_y + 1][index_x - 2]->getPlayerType() != m_chPlayerType
				&& vec[index_y + 1][index_x - 2]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
		if (index_x + 2 < MAPSIZE_WIDTH)
		{
			if (vec[index_y + 1][index_x + 2] != NULL && vec[index_y + 1][index_x + 2]->getPlayerType() != m_chPlayerType
				&& vec[index_y + 1][index_x + 2]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
	}

	if (index_y + 2 < MAPSIZE_HEIGHT)
	{
		if (index_x - 1 >= 0)
		{
			if (vec[index_y + 2][index_x - 1] != NULL && vec[index_y + 2][index_x - 1]->getPlayerType() != m_chPlayerType
				&& vec[index_y + 2][index_x - 1]->getNumCode() == CHESSPIECE_NUM_KNIGHT) return true;
		}
		if (index_x + 1 < MAPSIZE_WIDTH)
		{
			if (vec[index_y + 2][index_x + 1] != NULL && vec[index_y + 2][index_x + 1]->getPlayerType() != m_chPlayerType
				&& vec[index_y + 2][index_x + 1]->getcheckedflag() == CHESSPIECE_NUM_KNIGHT) return true;
		}
	}

	return false;
}

bool ChessPiece::PawnCheck(vector<vector<ChessPiece*>> vec, int index_x, int index_y)
{
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
							&& vec[index_y + 1][index_x + 1]->getNumCode() == CHESSPIECE_NUM_PAWN) return true;
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
							&& vec[index_y + 1][index_x - 1]->getNumCode() == CHESSPIECE_NUM_PAWN) return true;
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
							&& vec[index_y - 1][index_x + 1]->getNumCode() == CHESSPIECE_NUM_PAWN) return true;
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
							&& vec[index_y - 1][index_x - 1]->getNumCode() == CHESSPIECE_NUM_PAWN) return true;
					}
				}
			}
		}
	}

	return false;
}