#include "Coins/Coins.h"

Coins::Coins()
{
	this->initVariables();
	this->initSprite();
}

Coins::~Coins()
{

}

void Coins::update()
{
	this->updateAnimations();
}
void Coins::initVariables()
{
	this->m_animationTimer.restart();
}

void Coins::initSprite()
{
	if (!this->m_textureSheet.loadFromFile("../data/SpriteSheets/Coins/coinsSpriteSheet.png"))
		std::cout << "ERROR::Could not load PiranhaPlant sprite sheet" << "\n";
	this->m_sprite.setTexture(this->m_textureSheet);
	this->m_currentFrame = sf::IntRect(0, 0, 8, 16);
	this->m_sprite.setTextureRect(this->m_currentFrame);
	this->m_sprite.setScale(6.f, 6.f);
}

void Coins::updateAnimations()
{
	if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.15f)
	{
		this->m_currentFrame.top = 0;
		this->m_currentFrame.left += 8;

		if (this->m_currentFrame.left > 24.f)
		{
			this->m_currentFrame.left = 0;
		}

		this->m_animationTimer.restart();
		this->m_sprite.setTextureRect(this->m_currentFrame);
	}
}