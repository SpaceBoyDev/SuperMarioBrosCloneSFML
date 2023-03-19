#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Enemy
{
public:
	//Constructors //Destructors
	Enemy(const sf::Texture texture, const float scale, const sf::IntRect currentFrame);
	virtual ~Enemy();

	//GETTERS & SETTERS
	const float getGravity() const { return this->m_gravity; }
	const sf::Vector2f getVelocity() const { return this->m_velocity; }
	const sf::Sprite getSprite() const { return this->m_sprite; }

	void setGravity(const float gravity) { this->m_gravity = gravity; }
	virtual void setIsAlive(const bool isAlive) { this->m_isAlive = isAlive; }
	virtual void setPosition(const float x, const float y) { this->m_sprite.setPosition(x,y); }

	void update();
	void render(sf::RenderTarget& target);

	void initVariables();
	void initSprite();

	void updateAnimations();
	void initColliders();
	void updateColliders();
	

protected:
	//Colliders
	sf::RectangleShape m_collider;
	sf::Vector2f m_colliderSize;

	sf::RectangleShape m_colliderBottom;

	//sf::RectangleShape m_colliderTop;

	//States
	bool m_isAlive;

	//Anims
	sf::Sprite m_sprite;
	sf::Texture m_textureSheet;
	sf::Clock m_animationTimer;
	sf::IntRect m_currentFrame;
	float m_scale;

	//Physics
	sf::Vector2f m_velocity;
	float m_gravity;
};