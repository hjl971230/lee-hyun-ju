#include "Enemy.h"

Enemy::Enemy()
{
	m_point.x = 0;
	m_point.y = 0;
}

Enemy::~Enemy()
{

}

void Enemy::Update()
{
	m_point.x++;
	m_halfpoint.x++;
}