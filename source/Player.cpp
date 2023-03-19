#include "Player.h"

//Constructors //Destructors
Player::Player()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

Player::~Player()
{
	
}

//-->PUBLIC FUNCTIONS<--
//UPDATE
void Player::update()
{
	if (this->m_isAlive)
	{
		this->updateAnimations();
		this->updateMovement();
		this->updatePhysics();
	}
	else
	{
		std::cout << "\nDEP\n";
		this->deathAnim();
	}
}
//RENDER
void Player::render(sf::RenderTarget& target)
{
	target.draw(this->m_sprite);
}

void Player::reInit()
{
	this->initVariables();
	this->initTexture();
	this->initSprite();
	this->initAnimation();
	this->initPhysics();
}

void Player::move(const float dirX, const float dirY)
{
	this->m_velocity.x += dirX * this->m_acceleration;
	this->m_velocity.y += dirY * this->m_jumpForce;

	if (std::abs(this->m_velocity.x) > this->m_maxVelocity)
	{
		this->m_velocity.x = this->m_maxVelocity * ((this->m_velocity.x < 0) ? -1.f : 1.f);
	}
}

void Player::bounceJump()
{
	this->m_isUpPressed = true;
	this->move(0.f, -0.5f);
	this->m_isGrounded = false;
	this->m_applyGravity = true;
}
void Player::deathAnim()
{
	this->m_animState = playerAnimStates::dead;
	this->m_applyGravity = false;
	this->m_currentFrame.top = 48.f;
	this->m_currentFrame.left = 0.f;
	this->m_sprite.setTextureRect(this->m_currentFrame);
	if (this->m_animGoUp)
	{
		this->m_animationTimer.restart();
		this->m_animGoUp = false;
	}

	if (this->m_animationTimer.getElapsedTime().asSeconds() <= 0.8f && this->m_animationTimer.getElapsedTime().asSeconds() > 0.3f)
	{
		this->m_sprite.move(0, -10 * 2);
	}
	else if (this->m_animationTimer.getElapsedTime().asSeconds() > 1.2f && this->m_animationTimer.getElapsedTime().asSeconds() < 5.2f)
	{
		this->m_sprite.move(0, 10 * 3);
	}

}
//-->PRIVATE FUNCTIONS<--
void Player::initVariables()
{
	this->m_coins = 0;
	this->m_animState = playerAnimStates::right;
	this->m_sprite.setScale(7.f, 7.f);
	this->m_sprite.setOrigin(0.f, 0.f);
	this->m_isUpPressed = true;
	this->m_canMove = true;
	this->m_isAlive = true;
}

void Player::initTexture()
{
	if (!this->m_textureSheet.loadFromFile("../data/SpriteSheets/superMarioSpriteSheet.png"))
		std::cout << "ERROR::Could not load player sprite sheet" << "\n";
}

void Player::initSprite()
{
	this->m_sprite.setTexture(this->m_textureSheet);
	this->m_currentFrame = sf::IntRect(0, 0, 16, 16);
	this->m_sprite.setTextureRect(this->m_currentFrame);
	this->m_sprite.setScale(7.f, 7.f);
	this->m_sprite.setPosition(sf::Vector2f(500, 500));
}

void Player::updateAnimations()
{
	if (this->m_animState == playerAnimStates::idle)
	{

		if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.07f)
		{
			this->m_isFalling = false;
			this->m_currentFrame.top = 0;
			this->m_currentFrame.left = 0;
			this->m_animationTimer.restart();
			this->m_sprite.setTextureRect(this->m_currentFrame);
		}
	}
	else if (this->m_animState == playerAnimStates::right)
	{
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.06f)
		{
			this->m_isFalling = false;
			this->m_currentFrame.left += 18.f;
			this->m_currentFrame.top = 16;
			if (this->m_currentFrame.left >= 54.f)
			{
				this->m_currentFrame.left = 0;
			}
			
			this->m_animationTimer.restart();
			this->m_sprite.setTextureRect(this->m_currentFrame);
		}
	}
	else if (this->m_animState == playerAnimStates::left)
	{
		if (this->m_animationTimer.getElapsedTime().asSeconds() >= 0.06f)
		{
			this->m_isFalling = false;
			this->m_currentFrame.left += 18.f;
			this->m_currentFrame.top = 16.f;
			if (this->m_currentFrame.left >= 54.f)
			{
				this->m_currentFrame.left = 0;
			}
			this->m_animationTimer.restart();
			this->m_sprite.setTextureRect(this->m_currentFrame);
		}

	}
	else if (this->m_animState == playerAnimStates::jumping)
	{
		this->m_isFalling = false;
		this->m_animationTimer.restart();
		this->m_currentFrame.left = 0.f;
		this->m_currentFrame.top = 32.f;
		this->m_sprite.setTextureRect(this->m_currentFrame);
	}
	else if (this->m_animState == playerAnimStates::falling)
	{
		this->m_isFalling = true;
		this->m_isGrounded = false;
		this->m_currentFrame.left = 0.f;
		this->m_currentFrame.top = 32.f;
		this->m_animationTimer.restart();
		this->m_sprite.setTextureRect(this->m_currentFrame);
	}
}

void Player::updateMovement()
{

	this->m_animState = playerAnimStates::idle;
	if (this->m_canMove)
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
		{
			this->move(-1.f, 0.f);
			if (m_isGrounded)
			{
				this->m_animState = playerAnimStates::left;
			}
			this->m_sprite.setOrigin(this->m_sprite.getGlobalBounds().width / 7.f, 0);
			this->m_sprite.setScale(-7.f, 7.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
		{
			this->move(1.f, 0.f);
			if (m_isGrounded)
			{
				this->m_animState = playerAnimStates::right;
			}
			this->m_sprite.setScale(7.f, 7.f);
			this->m_sprite.setOrigin(0.f, 0.f);
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && this->m_isGrounded && !this->m_isUpPressed)
		{

			this->m_isUpPressed = true;
			this->move(0.f, -1.f);
			this->m_isGrounded = false;
			this->m_applyGravity = true;
			std::cout << "trying to jump" << std::endl;

		}
		else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
		{
			this->m_isUpPressed = false;
		}
	}

	if (this->m_velocity.y > 0)
	{
		this->m_animState = playerAnimStates::falling;

	}
	else if (this->m_velocity.y < 0)
	{
		this->m_animState = playerAnimStates::jumping;
	}

}

void Player::initPhysics()
{
	this->m_maxVelocity = 10.f;
	this->m_minVelocity = 2.f;
	this->m_acceleration = 3.f;
	this->m_drag = 0.87f;
	this->m_gravity = 3.5f;
	this->m_maxVelocityY = 50.f;
	this->m_minVelocityY = 0.8f;
	this->m_isGrounded = false;
	this->m_jumpForce = 100.f;
	this->m_applyGravity = true;
	this->m_colliderJump.setSize(sf::Vector2f(12.f * 5.f, 5.f));
	this->m_colliderJump.setFillColor(sf::Color::Red);
	this->m_colliderHead.setSize(sf::Vector2f(12.f * 5.f, 5.f));
	this->m_colliderHead.setFillColor(sf::Color::Red);
	this->m_collider.setSize(sf::Vector2f(16.f * 5.f, 12.f * 5.f));
	this->m_collider.setFillColor(sf::Color(50,50,50,200));
	this->m_collider.setPosition(sf::Vector2f(200.f, 900.f));
}

void Player::updatePhysics()
{
	//GRAVITY
	if (m_applyGravity)
	{
		this->m_velocity.y += 1.0 * this->m_gravity;
	}
	
	if (std::abs(this->m_velocity.x) > this->m_maxVelocityY)
	{
		this->m_velocity.y = this->m_maxVelocityY * ((this->m_velocity.y < 0) ? -1.f : 1.f);
	}

	this->m_velocity *= this->m_drag;

	if (std::abs(this->m_velocity.x) < this->m_minVelocity)
	{
		this->m_velocity.x = 0.f;
	}

	this->m_collider.move(this->m_velocity);
	this->m_colliderJump.setPosition(this->m_collider.getPosition().x + 10.f, this->m_collider.getPosition().y + this->m_collider.getGlobalBounds().height + 30.f);
	this->m_colliderHead.setPosition(this->m_collider.getPosition().x + 10.f, this->m_collider.getPosition().y - 20.f);
	this->m_sprite.setPosition(this->m_collider.getPosition().x - 16.f, this->m_collider.getGlobalBounds().top - 20.f);
}

void Player::initAnimation()
{
	this->m_animGoUp = true;
	this->m_animationTimer.restart();
}


