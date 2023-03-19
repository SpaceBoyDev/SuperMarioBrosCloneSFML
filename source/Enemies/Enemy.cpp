#include "Enemies/Enemy.h"

Enemy::Enemy(const sf::Texture texture, const float scale, const sf::IntRect currentFrame) :
	m_textureSheet(texture),
	m_scale(scale),
	m_currentFrame(currentFrame)
{
	this->initVariables();
	this->initSprite();
	this->initColliders();
}

Enemy::~Enemy()
{

}

void Enemy::update()
{
	this->updateAnimations();
	this->updateColliders();
}

void Enemy::render(sf::RenderTarget& target)
{
	//target.draw(this->m_sprite);
	//target.draw(this->m_collider);
	//target.draw(this->m_colliderBottom);
	//target.draw(this->m_colliderTop);
}

void Enemy::updateAnimations()
{
	if (this->m_isAlive)
	{
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.4f)
		{
			this->m_currentFrame.top = 0;
			this->m_currentFrame.left += 16.f;
			if (this->m_currentFrame.left > 16.f)
			{
				this->m_currentFrame.left = 0;
			}
			this->m_animationTimer.restart();
			this->m_sprite.setTextureRect(this->m_currentFrame);
		}
	}
}

void Enemy::initColliders()
{
	this->m_colliderSize = sf::Vector2f(this->m_sprite.getGlobalBounds().width / 1.2f, this->m_sprite.getGlobalBounds().height / 1.1f);
	this->m_collider.setSize(this->m_colliderSize);
	this->m_collider.setFillColor(sf::Color((50, 50, 50, 200)));
}

void Enemy::updateColliders()
{
	this->m_collider.setPosition(this->m_sprite.getPosition().x + (this->m_sprite.getGlobalBounds().width / 12),
		this->m_sprite.getPosition().y + (this->m_sprite.getGlobalBounds().height - (this->m_sprite.getGlobalBounds().height / 1.1f)));
}

void Enemy::initVariables()
{
	this->m_isAlive = true;
	this->m_gravity = 2.f;
}

void Enemy::initSprite()
{
	this->m_animationTimer.restart();
	this->m_sprite.setTexture(this->m_textureSheet);
	this->m_sprite.setTextureRect(this->m_currentFrame);
	this->m_sprite.setScale(this->m_scale, this->m_scale);
	this->m_sprite.setPosition(sf::Vector2f(500, 500));
}