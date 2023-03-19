#include "Enemies/PiranhaPlant.h"

PiranhaPlant::PiranhaPlant()
{
	this->initVariables();
	this->initSprite();
}

PiranhaPlant::~PiranhaPlant()
{

}

void PiranhaPlant::update()
{
	this->updateAnimations();
}
void PiranhaPlant::initVariables()
{
	this->m_animationTimer.restart();
}

void PiranhaPlant::initSprite()
{
	if (!this->m_textureSheet.loadFromFile("../data/SpriteSheets/Enemies/piranhaPlantSpriteSheet.png"))
		std::cout << "ERROR::Could not load PiranhaPlant sprite sheet" << "\n";
	this->m_sprite.setTexture(this->m_textureSheet);
	this->m_currentFrame = sf::IntRect(0, 0, 16, 24);
	this->m_sprite.setTextureRect(this->m_currentFrame);
	this->m_sprite.setScale(6.f, 6.f);
}

void PiranhaPlant::updateAnimations()
{
	if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.25f)
	{
		this->m_currentFrame.top = 0;
		this->m_currentFrame.left += 16;

		if (this->m_currentFrame.left > 16.f)
		{
			this->m_currentFrame.left = 0;
		}

		this->m_animationTimer.restart();
		this->m_sprite.setTextureRect(this->m_currentFrame);
	}
}