#pragma once

#include <iostream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class Coins
{
public:
	Coins();
	virtual ~Coins();

	//SETTERS & GETTERS
	void setPosition(const float x, const float y) { this->m_sprite.setPosition(x, y); }

	const sf::Sprite getSprite() const { return this->m_sprite; }
	const sf::FloatRect getGlobalBounds() const { return this->m_sprite.getGlobalBounds(); }

	//FUNCTIONS
	void update();
	//void render(sf::RenderTarget& target);

private:
	//Sprite
	sf::Sprite m_sprite;
	sf::Texture m_textureSheet;
	sf::IntRect m_currentFrame;

	//Anims
	sf::Clock m_animationTimer;

	//Functions
	void initVariables();
	void initSprite();
	void updateAnimations();
};