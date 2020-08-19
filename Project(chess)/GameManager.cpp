#include "GameManager.h"

GameManager* GameManager::m_this = NULL;

GameManager::GameManager()
{
	m_bClickflag = false;
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
		if (count <= 15)
		{
			for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
			{
				ChessPieceNumSetting(ChessNum, player, count);
				(*iter2) = ChessPieceFactory(hWnd, ChessNum, x, y, player);
				(*iter2)->Init(hWnd, x, y);
				x += BMPSIZE_WIDTH / 2;
				count++;
			}
		}
		y += BMPSIZE_HEIGHT / 2;
		if (count >= 15)
		{
			player = PLAYER_WHITE;
			x = MAP_X;
			y = MAP_Y + ((BMPSIZE_HEIGHT / 2) * 6);
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
		break;
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

void GameManager::Click(int x, int y)
{
	if (!m_bClickflag)
	{
		m_bClickflag = true;
		for (vector<vector<ChessPiece*>>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
		{
			for (vector<ChessPiece*>::iterator iter2 = (*iter).begin(); iter2 != (*iter).end(); iter2++)
			{
				if ((*iter2) != NULL)
				{
					if ((*iter2)->getsize().cx <= x && x <= (*iter2)->getsize().cx + BMPSIZE_WIDTH
						&& (*iter2)->getsize().cy <= y && y <= (*iter2)->getsize().cy + BMPSIZE_HEIGHT)
					{
						(*iter2)->MoveCalculate();
					}
				}
			}
		}
	}
}