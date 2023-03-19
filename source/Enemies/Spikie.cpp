#include "Enemies/Spikie.h"

Spikie::~Spikie()
{

}

void Spikie::update()
{
	Enemy::update();
	if (m_startMovement)
	{
		this->movement();
	}
}

void Spikie::initVariables()
{
	this->m_direction = -1;
	this->m_startMovement = false;
}

void Spikie::reInit()
{
	this->initVariables();
}

void Spikie::movement()
{
	this->m_sprite.move(this->m_direction * 3, 0);
}

void Spikie::changeDirection()
{
	this->m_direction *= -1; 
	if (this->m_direction == -1)
	{
		this->m_sprite.setOrigin(0.f, 0.f);
		this->m_sprite.setScale(6.f, 6.f);
	}
	else
	{
		this->m_sprite.setOrigin(this->m_sprite.getGlobalBounds().width / 6.f, 0.f);
		this->m_sprite.setScale(-6.f, 6.f);
	}
}