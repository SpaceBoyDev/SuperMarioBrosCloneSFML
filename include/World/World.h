#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <string>
#include <fstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

#include "Enemies/Goomba.h"
#include "Enemies/Spikie.h"
#include "Enemies/PiranhaPlant.h"
#include "Coins/Coins.h"

class World
{
public:
	World();
	virtual ~World();
	//FUNCTIONS
	//TILES
	const std::vector<sf::Sprite> getTiles() const { return this->m_tilesVector; }
	const int getTilesVectorSize() const { return this->m_tilesVectorSize; }
	const bool getIsWorldBuilt() const { return this->m_isWorldBuilt; }
	//FLAG POLE
	const std::vector<sf::Sprite> getFlagPole() const { return this->m_flagPoleVector; }
	const int getFlagPoleVectorSize() const { return this->m_flagPoleVectorSize; }
	//Goombas functions
	const std::vector<Goomba*> getGoombas() const { return this->m_goombaVector; }
	const int getGoombaVectorSize() const { return this->m_goombaVectorSize; }
	void deleteGoomba(const int n);
	//Spikies functions
	const std::vector<Spikie*> getSpikies() const { return this->m_spikieVector; }
	const int getSpikieVectorSize() const { return this->m_spikieVectorSize; }
	//Piranha plants functions
	const std::vector<PiranhaPlant*> getPiranhaPlants() const { return this->m_piranhaPlantVector; }
	const int getPiranhaPlantVectorSize() const { return this->m_piranhaPlantVectorSize; }
	//Coins functions
	const std::vector<Coins*> getCoins() const { return this->m_coinsVector; }
	const int getCoinsVectorSize() const { return this->m_coinsVectorSize; }
	void deleteCoin(const int n);
	
	void update();
	void render(sf::RenderTarget& target);
	void reInit();

private:
	//TILES
	sf::Vector2f m_tilesPos;

	std::vector<sf::Sprite> m_noCollisionVector;
	int m_noCollisionVectorSize;

	std::vector<sf::Sprite> m_tilesVector;
	int m_tilesVectorSize;

	std::vector<sf::Sprite> m_flagPoleVector;
	int m_flagPoleVectorSize;

	sf::Sprite m_floor;
	sf::Sprite m_bricks;
	sf::Sprite m_slab;
	sf::Sprite m_questionBlock;
	sf::Sprite m_pipeTopLeft;
	sf::Sprite m_pipeTopRight;
	sf::Sprite m_pipeBottomLeft;
	sf::Sprite m_pipeBottomRight;
	sf::Sprite m_cloud;
	sf::Sprite m_bush;
	
	sf::Sprite m_flagPoleTop;
	sf::Sprite m_flagPole;

	sf::Texture m_tileSet;

	//ENEMIES
	//Goomba
	std::vector<Goomba*> m_goombaVector;
	Goomba* m_goomba;
	sf::Texture m_goombaTexture;
	sf::IntRect m_goombaFrame;
	int m_goombaVectorSize;
	//Spikie
	std::vector<Spikie*> m_spikieVector;
	Spikie* m_spikie;
	sf::Texture m_spikieTexture;
	sf::IntRect m_spikieFrame;
	int m_spikieVectorSize;
	//PiranhaPlant
	std::vector<PiranhaPlant*> m_piranhaPlantVector;
	PiranhaPlant* m_piranhaPlant;
	int m_piranhaPlantVectorSize;

	//Coins
	std::vector<Coins*> m_coinsVector;
	Coins* m_coinsPlant;
	int m_coinsVectorSize;

	//WORLD FILE
	std::ifstream m_worldFile;
	std::string m_worldString;
	long tilePosX;
	long tilePosY;

	bool m_isWorldBuilt;

	//FUNCTIONS
	void initTilesSprites();
	void initVariables();
	void initEnemies();

	void buildWorld();
};