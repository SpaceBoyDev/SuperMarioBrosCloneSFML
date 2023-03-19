#pragma once

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

#include "Player.h"
#include "World/World.h"
#include "UI/UIManager.h"

//This class acts as the game engine.
class Game
{
public:
	//CONSTRUCTOR
	Game();
	//DESTRUCTOR
	virtual ~Game();

	//SETTERS & GETTERS
	float getDelta() const { return this->m_deltaTime.asSeconds(); }
	const sf::RenderWindow& getWindow() const { return this->m_window; }
	const bool running() const;
	const bool getEndGame() const;

	//FUNCTIONS
	void update();
	void render();
	void pollEvents();
	void reInit(const float timeToWait);

private:
	//Player
	Player* m_player;

	//World
	World* m_world;

	//UIManager
	UIManager* m_UIManager;

	//Variables
	//Window
	sf::RenderWindow m_window;
	sf::VideoMode m_videoMode;
	sf::View m_view;
	sf::Event m_ev;

	//Resources
	sf::Font m_font;

	//Text
	sf::Text m_uiText;

	//Game logic
	bool m_endGame;
	bool m_reInit;
	sf::Clock m_deltaClock;
	sf::Time m_deltaTime = m_deltaClock.restart();
	sf::Clock m_crono;
	bool m_restartCrono;

	//Functions
	void updateDeltaTime();
	void initVariables();
	void initWindow();
	void updateView();
	void winGame();

	bool isInView(sf::FloatRect sprite);

	//Player functions
	void renderPlayer();
	void updatePlayer();
	void initPlayer();
	void updatePlayerCollision();

	//World functions
	void renderWorld();
	void initWorld();

	//Enemies functions
	void updateEnemies();
	void enemiesCollisions();

	//UIManager functions
	void initUIManager();
	void updateUIManager(const int n);
	void renderUIManager(sf::RenderTarget& target);
};

