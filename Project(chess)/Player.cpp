#include "Player.h"

Player::Player()
{
	m_vecChessPieces.reserve(CHESSPIECE_SIZE);
	m_vecChessPieces.assign(CHESSPIECE_SIZE, NULL);
}

Player::~Player()
{
	ChessPieceRelease();
}

void Player::ChessPieceInit(HWND hWnd, int x, int y, int player)
{
	int count = 0;
	int ChessNum = CHESSPIECE_NUM_PAWN;
	for (vector<ChessPiece*>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
	{
		if (count == CHESSPIECE_SIZE / 2)
		{
			x = MAP_X;
			y += BMPSIZE_HEIGHT / 2;
		}
		ChessPieceNumSetting(ChessNum, player, count);
		(*iter) = ChessPieceFactory(hWnd, ChessNum, x, y);
		x += BMPSIZE_WIDTH / 2;
		count++;
	}
}

void Player::ChessPieceNumSetting(int& num, int player, int count)
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

void Player::ChessPieceDraw(HDC hdc)
{
	for (vector<ChessPiece*>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
		(*iter)->Draw(hdc);
}

ChessPiece* Player::ChessPieceFactory(HWND hWnd, int num, int x, int y)
{
	ChessPiece* tmp = NULL;
	switch (num)
	{
	case CHESSPIECE_NUM_PAWN:
		tmp = new Pawn(m_chPlayerType);
		break;
	case CHESSPIECE_NUM_KNIGHT:
		tmp = new Knight(m_chPlayerType);
		break;
	case CHESSPIECE_NUM_BISHOP:
		tmp = new Bishop(m_chPlayerType);
		break;
	case CHESSPIECE_NUM_ROOK:
		tmp = new Rook(m_chPlayerType);
		break;
	case CHESSPIECE_NUM_QUEEN:
		tmp = new Queen(m_chPlayerType);
		break;
	case CHESSPIECE_NUM_KING:
		tmp = new King(m_chPlayerType);
		break;
	default:
		break;
	}
	tmp->FileNameSetting();
	tmp->Init(hWnd, x, y);
	return tmp;
}

void Player::ChessPieceRelease()
{
	for (vector<ChessPiece*>::iterator iter = m_vecChessPieces.begin(); iter != m_vecChessPieces.end(); iter++)
		delete (*iter);
}