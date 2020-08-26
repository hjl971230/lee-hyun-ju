#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_bClickflag = true;
	m_chturn = WHITE;
	m_SelectPiece = NULL;
	m_bmoveflag = false;
	m_iblackdeathcount = 0;
	m_iwhitedeathcount = 0;
}

GameManager::~GameManager()
{
	MapRelease();
	ChessPieceRelease();
	PiecesCemeteryRelease();
}

void GameManager::GameInit(HWND hWnd)
{
	MapInit(hWnd);
	ChessPieceInit(hWnd); 
	PiecesCemeteryinit();
}

void GameManager::MapInit(HWND hWnd)
{
	vector<BitMap> size;
	BitMap bsize;
	size.reserve(MAPSIZE_WIDTH);
	MapRelease();
	m_map.reserve(MAPSIZE_HEIGHT);
	m_map.assign(MAPSIZE_HEIGHT, size);
	char filename[128];
	int num = 1;
	int x = MAP_X;
	int y = MAP_Y;
	int height = 0;
	for (vector<vector<BitMap>>::iterator iter = m_map.begin(); iter != m_map.end(); iter++)
	{
		(*iter).assign(MAPSIZE_WIDTH, bsize);
		x = MAP_X;
		for (vector<BitMap>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			sprintf(filename, TEXT("block0%d.bmp"), num);
			(*iter2).setFileName(filename);
			(*iter2).Init(hWnd, x, y);
			if (x != MAP_X + ((BMPSIZE_WIDTH / 2) * (MAPSIZE_WIDTH - 1)))
			{
				if (num == 1)num = 2;
				else num = 1;
			}
			x += BMPSIZE_WIDTH / 2;
		}
		y += BMPSIZE_HEIGHT / 2;
	}
}

void GameManager::MapRelease()
{
	if (!m_map.empty())
		m_map.clear();
}

void GameManager::MapDraw(HDC hdc)
{
	for (vector<vector<BitMap>>::iterator iter = m_map.begin(); iter != m_map.end(); iter++)
	{
		for (vector<BitMap>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			(*iter2).Draw(hdc);
		}
	}
}

void GameManager::PiecesCemeteryinit()
{
	m_vecPiecesCemetery[PLAYER_BLACK].clear();
	m_vecPiecesCemetery[PLAYER_WHITE].clear();
	ChessPiece* size = NULL;
	m_vecPiecesCemetery[PLAYER_BLACK].reserve(CHESSPIECE_SIZE);
	m_vecPiecesCemetery[PLAYER_BLACK].assign(CHESSPIECE_SIZE, size);
	m_vecPiecesCemetery[PLAYER_WHITE].reserve(CHESSPIECE_SIZE);
	m_vecPiecesCemetery[PLAYER_WHITE].assign(CHESSPIECE_SIZE, size);
}

void GameManager::ChessPieceInit(HWND hWnd)
{
	m_vecChessPieces.clear();
	int x = MAP_X;
	int y = MAP_Y;
	int index_x = 0;
	int index_y = 0;
	int count = 0;
	int ChessNum = CHESSPIECE_NUM_PAWN;
	int player = PLAYER_BLACK;
	vector<ChessPiece*> size;
	size.reserve(MAPSIZE_WIDTH);
	size.assign(MAPSIZE_WIDTH, NULL);
	m_vecChessPieces.reserve(MAPSIZE_HEIGHT);
	m_vecChessPieces.assign(MAPSIZE_HEIGHT, size);
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		x = MAP_X;
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			ChessPieceNumSetting(ChessNum, player, count);
			(*iter2) = ChessPieceFactory(hWnd, ChessNum, x, y, player);
			if ((*iter2) != NULL) (*iter2)->Init(hWnd, x, y);
			x += BMPSIZE_WIDTH / 2;
			count++;
		}
		if (count >= 15) count = 0;
		y += BMPSIZE_HEIGHT / 2;
		index_y++;
		if (index_y >= 2 && index_y <= 5)
		{
			player = -1;
			count = 0;
		}
		else if (index_y == 6)
		{
			player = PLAYER_WHITE;
			count = 0;
		}
	}
}

void GameManager::ChessPieceNumSetting(int& num, int player, int count)
{
	if (player == PLAYER_BLACK)
	{
		switch (count)
		{
		case 0:
		case 7:
			num = CHESSPIECE_NUM_ROOK;
			break;
		case 1:
		case 6:
			num = CHESSPIECE_NUM_KNIGHT;
			break;
		case 2:
		case 5:
			num = CHESSPIECE_NUM_BISHOP;
			break;
		case 3:
			num = CHESSPIECE_NUM_QUEEN;
			break;
		case 4:
			num = CHESSPIECE_NUM_KING;
			break;
		default:
			num = CHESSPIECE_NUM_PAWN;
			break;
		}
	}
	else if(player == -1)
	{
		num = CHESSPIECE_NUM_EMPTY;
	}
	else
	{
		switch (count)
		{
		case 8:
		case 15:
			num = CHESSPIECE_NUM_ROOK;
			break;
		case 9:
		case 14:
			num = CHESSPIECE_NUM_KNIGHT;
			break;
		case 10:
		case 13:
			num = CHESSPIECE_NUM_BISHOP;
			break;
		case 11:
			num = CHESSPIECE_NUM_QUEEN;
			break;
		case 12:
			num = CHESSPIECE_NUM_KING;
			break;
		default:
			num = CHESSPIECE_NUM_PAWN;
			break;
		}
	}
}

void GameManager::ChessPieceDraw(HWND hWnd)
{
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if ((*iter2) != NULL)
			{
				(*iter2)->Draw(GetDC(hWnd));
				if((*iter2)->getcheckedflag())
					(*iter2)->CalculateDraw(hWnd, (*iter2)->getFileName(), (*iter2)->getPoint().x, (*iter2)->getPoint().y, false);
			}
		}
	}
		
}

ChessPiece* GameManager::ChessPieceFactory(HWND hWnd, int num, int x, int y, int player)
{
	ChessPiece* tmp = NULL;
	char ch = '\0';
	if (player == PLAYER_BLACK)
		ch = BLACK;
	else ch = WHITE;
	switch (num)
	{
	case CHESSPIECE_NUM_PAWN:
		tmp = new Pawn(ch);
		break;
	case CHESSPIECE_NUM_KNIGHT:
		tmp = new Knight(ch);
		break;
	case CHESSPIECE_NUM_BISHOP:
		tmp = new Bishop(ch);
		break;
	case CHESSPIECE_NUM_ROOK:
		tmp = new Rook(ch);
		break;
	case CHESSPIECE_NUM_QUEEN:
		tmp = new Queen(ch);
		break;
	case CHESSPIECE_NUM_KING:
		tmp = new King(ch);
		break;
	default:
		tmp = NULL;
		return tmp;
	}
	tmp->FileNameSetting();
	tmp->Init(hWnd, x, y);
	return tmp;
}

void GameManager::ChessPieceRelease()
{
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if ((*iter2) != NULL)
			{
				delete (*iter2);
				(*iter2) = NULL;
			}
		}
	}		
}

bool GameManager::SelectPiece(HWND hWnd, int x, int y)
{
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if ((*iter2) != NULL)
			{
				if ((*iter2)->getPoint().x <= x && x <= (*iter2)->getPoint().x + BMPSIZE_WIDTH / 2
					&& (*iter2)->getPoint().y <= y && y <= (*iter2)->getPoint().y + BMPSIZE_HEIGHT / 2
					&& m_chturn == (*iter2)->getPlayerType())
				{
					if (!(*iter2)->getClickflag())
					{
						if (m_SelectPiece != NULL)
							m_SelectPiece->setClickflag(false);
						(*iter2)->setClickflag(true);
						m_SelectPiece = (*iter2);
						return true;
					}
					else
					{
						if (m_SelectPiece != NULL)
							m_SelectPiece->setClickflag(false);
						(*iter2)->setClickflag(false);
						m_SelectPiece = NULL;
						return false;
					}
				}
			}
		}
	}
	return false;
}

bool GameManager::MovePiece(HWND hWnd, int x, int y)
{
	ChessPiece* tmp = NULL;

	tmp = m_SelectPiece->Move(hWnd, m_vecChessPieces, x, y, m_bmoveflag);
	if (m_SelectPiece->getNumCode() == CHESSPIECE_NUM_PAWN)
	{
		Promotion(hWnd);
	}
	if (m_bmoveflag)
	{
		if (tmp != NULL)
		{
			GotoCemetery(tmp);
			if (tmp->getNumCode() == CHESSPIECE_NUM_KING)
			{
				if (tmp->getPlayerType() == BLACK)
				{
					if (MessageBox(hWnd, TEXT("백 승리, 게임을 다시 하시겠습니까?"), TEXT("White Win"), MB_YESNO) == IDYES)
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						MapInit(hWnd);
						ChessPieceInit(hWnd);
						PiecesCemeteryinit();
						m_chturn = WHITE;
					}
					else
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						PostQuitMessage(0);
					}
				}
				else
				{
					if (MessageBox(hWnd, TEXT("흑 승리, 게임을 다시 하시겠습니까?"), TEXT("Black Win"), MB_YESNO) == IDYES)
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						MapInit(hWnd);
						ChessPieceInit(hWnd);
						PiecesCemeteryinit();
						m_chturn = WHITE;
					}
					else
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						PostQuitMessage(0);
					}
				}
			}
		}
		if (m_chturn == BLACK)
			m_chturn = WHITE;
		else m_chturn = BLACK;
		m_bmoveflag = false;
		m_SelectPiece->setClickflag(false);
		m_SelectPiece = NULL;
		return true;
	}
	else return false;
}

void GameManager::Promotion(HWND hWnd)
{
	ChessPiece* tmp = NULL;
	ChessPiece* Promotiontmp = NULL;
	int PromotionType = m_SelectPiece->Promotion(hWnd, m_vecChessPieces);
	int player = 0;
	if (m_SelectPiece->getPlayerType() == BLACK)
		player = PLAYER_BLACK;
	else player = PLAYER_WHITE;
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if ((*iter2) != NULL)
			{
				if ((*iter2) == m_SelectPiece)
				{
					if (m_SelectPiece->getpromotionflag())
					{
						Promotiontmp = (*iter2);
						tmp = ChessPieceFactory(hWnd, PromotionType,
							m_SelectPiece->getPoint().x, m_SelectPiece->getPoint().y, player);
						tmp->setfirstmoveflag(m_SelectPiece->getfirstmoveflag());
						(*iter2) = tmp;
						m_SelectPiece = (*iter2);
						delete Promotiontmp;
					}
				}
			}
		}
	}
}

void GameManager::Check(HWND hWnd)
{
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if ((*iter2) != NULL)
			{
				if ((*iter2)->getNumCode() != CHESSPIECE_NUM_KING)
				{
					(*iter2)->Check(hWnd, m_vecChessPieces);
				}
				if ((*iter2)->getNumCode() == CHESSPIECE_NUM_KING)
				{
					CheckMateCheck(hWnd, iter2);
				}
			}
		}
	}
}

void GameManager::CheckMateCheck(HWND hWnd, vector<ChessPiece*>::iterator iter)
{
	if ((*iter) != NULL)
	{
		if ((*iter)->getNumCode() == CHESSPIECE_NUM_KING && (*iter)->getcheckedflag())
		{
			(*iter)->CalculateDraw(hWnd, (*iter)->getFileName(), (*iter)->getPoint().x, (*iter)->getPoint().y, false);
			if ((*iter)->CheckMatecheck(m_vecChessPieces))
			{
				if ((*iter)->getPlayerType() == BLACK)
				{
					if (MessageBox(hWnd, TEXT("백 승리, 게임을 다시 하시겠습니까?"), TEXT("White Win"), MB_YESNO) == IDYES)
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						MapInit(hWnd);
						ChessPieceInit(hWnd);
						PiecesCemeteryinit();
						m_chturn = WHITE;
					}
					else
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						PostQuitMessage(0);
					}
				}
				else
				{
					if (MessageBox(hWnd, TEXT("흑 승리, 게임을 다시 하시겠습니까?"), TEXT("Black Win"), MB_YESNO) == IDYES)
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						MapInit(hWnd);
						ChessPieceInit(hWnd);
						PiecesCemeteryinit();
						m_chturn = WHITE;
					}
					else
					{
						MapRelease();
						ChessPieceRelease();
						PiecesCemeteryRelease();
						PostQuitMessage(0);
					}
				}
			}
			else
			{
				(*iter)->setcheckedflag(false);
				(*iter)->CalculateDraw(hWnd, (*iter)->getFileName(), (*iter)->getPoint().x, (*iter)->getPoint().y, true);
			}
		}
	}
}

void GameManager::CalculateDraw(HWND hWnd)
{
	if(m_SelectPiece != NULL) m_SelectPiece->MoveCalculate(hWnd, m_vecChessPieces);
}

void GameManager::GotoCemetery(ChessPiece* chesspiece)
{
	int size_x = BMPSIZE_WIDTH / 2;
	int size_y = BMPSIZE_HEIGHT / 2;
	static int add_black_x = 0;
	static int add_black_y = 0;
	static int add_white_x = 0;
	static int add_white_y = 0;
	if (chesspiece->getPlayerType() == BLACK)
	{
		if (m_iblackdeathcount % 2 == 0)
		{
			add_black_x = 0;
			add_black_y += size_y;
		}
		chesspiece->setPoint(180 + add_black_x, 50 + add_black_y);
		m_vecPiecesCemetery[PLAYER_BLACK][m_iblackdeathcount] = chesspiece;
		m_iblackdeathcount++;
		add_black_x += size_x;
	}
	else
	{
		if (m_iwhitedeathcount % 2 == 0)
		{
			add_white_x = 0;
			add_white_y += size_y;
		}
		chesspiece->setPoint(980 + add_white_x, 50 + add_white_y);
		m_vecPiecesCemetery[PLAYER_WHITE][m_iwhitedeathcount] = chesspiece;
		m_iwhitedeathcount++;
		add_white_x += size_x;
	}
}

void GameManager::PiecesCemeteryDraw(HDC hdc)
{
	for (int i = 0; i < PLAYERSIZE; i++)
	{
		for (vector<ChessPiece*>::iterator iter = m_vecPiecesCemetery[i].begin(); iter != m_vecPiecesCemetery[i].end(); iter++)
		{
			if ((*iter) != NULL)
				(*iter)->Draw(hdc);
		}
	}
}

void GameManager::PiecesCemeteryRelease()
{
	for (int i = 0; i < PLAYERSIZE; i++)
	{
		for (vector<ChessPiece*>::iterator iter = m_vecPiecesCemetery[i].begin(); iter != m_vecPiecesCemetery[i].end(); iter++)
		{
			if ((*iter) != NULL)
			{
				delete* iter;
				*iter = NULL;
			}
		}
	}
}