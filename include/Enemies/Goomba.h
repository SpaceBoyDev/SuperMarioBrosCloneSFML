#pragma once
#include "Enemies/Enemy.h"

class Goomba : public Enemy
{
public:
	//Constructors //Destructors
	Goomba(const sf::Texture texture, const float scale, const sf::IntRect currentFrame)
		: Enemy(texture, scale, currentFrame) 
	{
		this->initVariables();
	};
	virtual ~Goomba();

	//SETTERS & GETTERS
	virtual void setPosition(const float x, const float y) { this->m_sprite.setPosition(x, y); }
	virtual void setIsAlive(const bool isAlive) { this->m_isAlive = isAlive; }
	void changeDirection() { this->m_direction *= -1; }
	void setStartMovement(bool startMovement) { this->m_startMovement = startMovement; }

	const bool getStartMovement() const { return this->m_startMovement; }
	const bool getIsAlive() const { return this->m_isAlive; }
	const sf::FloatRect getGlobalBounds() const { return this->m_sprite.getGlobalBounds(); }
	const sf::FloatRect getGlobalBoundsCollider() const { return this->m_collider.getGlobalBounds(); }
	const sf::Vector2f getPosition() { return this->m_sprite.getPosition(); }

	void update();
	void reInit();

private:
	//Functions
	void initVariables();
	void movement();

	//MOVEMENT
	int m_direction;
	bool m_startMovement;

	//ANIMS
	sf::Texture m_textureSheet;
	sf::IntRect m_currentFrame;
	float m_scale;
};