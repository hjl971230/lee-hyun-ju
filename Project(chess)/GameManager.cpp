#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_bClickflag = true;
	m_chturn = WHITE;
	m_SelectPiece = NULL;
}

GameManager::~GameManager()
{
	MapRelease();
	ChessPieceRelease();
}

void GameManager::GameInit(HWND hWnd)
{
	MapInit(hWnd);
	ChessPieceInit(hWnd);
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

void GameManager::ChessPieceDraw(HDC hdc)
{
	for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
		{
			if((*iter2) != NULL)
				(*iter2)->Draw(hdc);
		}
	}
		
}

ChessPiece* GameManager::ChessPieceFactory(HWND hWnd, int num, int x, int y, int player)
{
	ChessPiece* tmp = NULL;
	char ch = '\0';
	if (player == PLAYER_BLACK)
		ch = 'b';
	else ch = 'w';
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
			if((*iter2) != NULL)
				delete (*iter2);
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
					if (m_SelectPiece == (*iter2))
					{
						(*iter2)->setClickflag(false);
						m_SelectPiece = NULL;
						return false;
					}
					if (!(*iter2)->getClickflag())
					{
						(*iter2)->setClickflag(true);
						m_SelectPiece = (*iter2);
						return true;
					}
					else
					{
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
					if ((*iter2)->getClickflag())
					{
						
						m_SelectPiece = (*iter2);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void GameManager::CalculateDraw(HWND hWnd)
{
	if(m_SelectPiece != NULL) m_SelectPiece->MoveCalculate(hWnd, m_vecChessPieces);
}