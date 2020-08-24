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