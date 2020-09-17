#include "Enemy.h"

Enemy::Enemy()
{
	m_point.x = 0;
	m_point.y = 0;
	m_iscroll_move = 0;
	m_simagenum = 0;
	firstcollideflag = false;
}

Enemy::~Enemy()
{

}