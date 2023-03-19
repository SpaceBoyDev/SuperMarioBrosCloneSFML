#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

enum playerAnimStates {
	idle = 0, 
	left, 
	right, 
	jumping, 
	falling,
	dead
};

//This class is the player
class Player
{
public:
	//Constructors //Destructors
	Player();
	virtual ~Player();

	//Getters & Setters
	//GETTERS
	const sf::Vector2f getPlayerVelocity() const { return this->m_velocity; }
	const sf::FloatRect getGlobalBounds() const { return this->m_sprite.getGlobalBounds(); }
	const sf::Vector2f getPlayerPos() const { return this->m_collider.getPosition(); }
	const bool getIsFalling() const { return this->m_isFalling; }
	const bool getCanMove() const { return this->m_canMove; }
	const bool getIsAlive() const { return this->m_isAlive; }
	const int getCoins() const { return this->m_coins; }
	
	//SETTERS
	void resetVelocityY() { this->m_velocity.y = 0; }
	void resetVelocityX() { this->m_velocity.x = 0; }
	void setPosition(const float posX, const float posY) { this->m_collider.setPosition(sf::Vector2f(posX, posY)); }
	void setIsGrounded(const bool isGrounded) { this->m_isGrounded = isGrounded; }
	void setApplyGravity(const bool apply) { this->m_applyGravity = apply; }
	void setCanMove(const bool canMove) { this->m_canMove = canMove; }
	void setIsAlive(const bool isAlive) { this->m_isAlive = isAlive; }
	void addCoins(const int coins) { this->m_coins += coins; }

	//COLLIDERS GETTERS
	const sf::FloatRect getGlobalBoundsCollider() const { return this->m_collider.getGlobalBounds(); }
	const sf::FloatRect getGlobalBoundsColliderJump() const { return this->m_colliderJump.getGlobalBounds(); }
	const sf::FloatRect getGlobalBoundsColliderHead() const { return this->m_colliderHead.getGlobalBounds(); }

	//Functions
	void update();
	void render(sf::RenderTarget& target);
	void reInit();

	void move(const float dirX, const float dirY);
	void bounceJump();
	void deathAnim();

private:
	sf::Sprite m_sprite;
	sf::Texture m_textureSheet;
	sf::Clock m_animationTimer;

	//Animation
	short m_animState;
	sf::IntRect m_currentFrame;
	bool m_animGoUp;

	//Movement
	bool m_isUpPressed;
	bool m_canMove;
	//Logic
	bool m_isAlive;
	int m_coins;

	//Physics
	sf::RectangleShape m_collider;
	sf::RectangleShape m_colliderJump;
	sf::RectangleShape m_colliderHead;
	sf::Vector2f m_velocity;
	float m_maxVelocity;
	float m_minVelocity;
	float m_maxVelocityY;
	float m_minVelocityY;
	float m_acceleration;
	float m_drag;
	float m_jumpForce;
	float m_gravity;
	bool m_applyGravity;
	bool m_isGrounded;
	bool m_isFalling;

	//Functions
	void initVariables();
	void initTexture();
	void initSprite();
	void initAnimation();
	void initPhysics();

	void updateAnimations();
	void updatePhysics();
	void updateMovement();
};