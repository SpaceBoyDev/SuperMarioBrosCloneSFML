#include "Enemies/Goomba.h"

Goomba::~Goomba()
{

}

void Goomba::update()
{
	Enemy::update();
	if (m_startMovement)
	{
		this->movement();
	}
}

void Goomba::initVariables()
{
	this->m_direction = -1;
	this->m_startMovement = false;
}

void Goomba::reInit()
{
	this->initVariables();
}

void Goomba::movement()
{
	this->m_sprite.move(this->m_direction * 3, 0);
}
