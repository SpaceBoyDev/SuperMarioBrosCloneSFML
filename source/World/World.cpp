#include "World/World.h"

//CONSTRUCTOR
World::World()
{
	this->initVariables();
	this->initEnemies();
	this->initTilesSprites();
	this->buildWorld();
}

//DESTRUCTOR
World::~World()
{
	//delete this->m_goomba;

	for (size_t i = 0; i < this->m_goombaVectorSize; i++)
	{
		delete this->m_goombaVector[i];
	}

	for (size_t i = 0; i < this->m_spikieVectorSize; i++)
	{
		delete this->m_spikieVector[i];
	}

	for (size_t i = 0; i < this->m_piranhaPlantVectorSize; i++)
	{
		delete this->m_piranhaPlantVector[i];
	}

	for (size_t i = 0; i < this->m_coinsVectorSize; i++)
	{
		delete this->m_coinsVector[i];
	}

	this->m_goombaVector.clear();
	this->m_spikieVector.clear();
	this->m_piranhaPlantVector.clear();
	this->m_noCollisionVector.clear();
	this->m_coinsVector.clear();
}

//-->PUBLIC FUNCTIONS<--
void World::deleteGoomba(const int n)
{
	delete this->m_goombaVector[n];
	this->m_goombaVector.erase(this->m_goombaVector.begin() + n);
	this->m_goombaVectorSize = this->m_goombaVector.size();
}

void World::deleteCoin(const int n)
{
	delete this->m_coinsVector[n];
	this->m_coinsVector.erase(this->m_coinsVector.begin() + n);
	this->m_coinsVectorSize = this->m_coinsVector.size();
}

void World::update()
{
	for (size_t i = 0; i < this->getGoombaVectorSize(); i++)
	{
		this->getGoombas()[i]->update();
	}

	for (size_t i = 0; i < this->getSpikieVectorSize(); i++)
	{
		this->getSpikies()[i]->update();
	}

	for (size_t i = 0; i < this->getPiranhaPlantVectorSize(); i++)
	{
		this->getPiranhaPlants()[i]->update();
	}

	for (size_t i = 0; i < this->getCoinsVectorSize(); i++)
	{
		this->getCoins()[i]->update();
	}

}

void World::render(sf::RenderTarget& target)
{
	if (m_isWorldBuilt)
	{
		//No Collision tiles
		for (size_t i = 0; i < this->m_noCollisionVectorSize; i++)
		{
			target.draw(this->m_noCollisionVector[i]);
		}
		//Piranha Plants
		for (size_t i = 0; i < this->m_piranhaPlantVector.size(); i++)
		{
			target.draw(this->m_piranhaPlantVector[i]->getSprite());
		}
		//Tiles
		for (size_t i = 0; i < this->m_tilesVector.size(); i++)
		{
			target.draw(this->m_tilesVector[i]);
		}
		//Flag pole
		for (size_t i = 0; i < this->m_flagPoleVector.size(); i++)
		{
			target.draw(this->m_flagPoleVector[i]);
		}

		//Goombas
		for (size_t i = 0; i < this->m_goombaVector.size(); i++)
		{
			target.draw(this->m_goombaVector[i]->getSprite());
		}
		//Spikies
		for (size_t i = 0; i < this->m_spikieVector.size(); i++)
		{
			target.draw(this->m_spikieVector[i]->getSprite());
		}
		//Coins
		for (size_t i = 0; i < this->m_coinsVectorSize; i++)
		{
			target.draw(this->m_coinsVector[i]->getSprite());
		}

	}
}

void World::reInit()
{
	this->m_flagPoleVector.clear();
	this->m_coinsVector.clear();
	this->m_noCollisionVector.clear();
	this->m_piranhaPlantVector.clear();
	this->m_tilesVector.clear();
	this->m_goombaVector.clear();
	this->m_spikieVector.clear();
	this->initVariables();
	this->initEnemies();
	this->initTilesSprites();
	this->buildWorld();
}

//-->PRIVATE FUNCTIONS<--
void World::initVariables()
{
	this->m_isWorldBuilt = false;

	this->tilePosX = 0;
	this->tilePosY = 0;
	this->m_tilesPos = sf::Vector2f(0.f, 0.f);
}

void World::buildWorld()
{
	char c;
	this->m_worldFile.open("../data/World/level1.txt");

	if (this->m_worldFile.is_open())
	{
		while (this->m_worldFile.get(c))
		{
			std::cout << c;
			switch (c)
			{
			case ';': //GO NEXT LINE

				this->m_tilesPos.x = 0.f;
				this->m_tilesPos.y += 96.f;
				std::cout << std::endl;
				break;
			case '0': //BLANK SPACE
				this->m_tilesPos.x += 96.f;
				break;
			case '1': //FLOOR
				this->m_tilesVector.push_back(this->m_floor);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '2': //BRICKS
				this->m_tilesVector.push_back(this->m_bricks);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '3': //QUESTION BLOCKS
				this->m_tilesVector.push_back(this->m_questionBlock);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '4': //SLABS
				this->m_tilesVector.push_back(this->m_slab);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '5': //PIPE PARTS
				this->m_tilesVector.push_back(this->m_pipeTopLeft);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '6':
				this->m_tilesVector.push_back(this->m_pipeTopRight);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '7':
				this->m_tilesVector.push_back(this->m_pipeBottomLeft);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '8':
				this->m_tilesVector.push_back(this->m_pipeBottomRight);
				this->m_tilesVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case '9': //COINS
				this->m_coinsVector.push_back(new Coins());
				this->m_coinsVector.back()->setPosition(m_tilesPos.x + 24.f, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case 'T': //FLAG POLE TOP
				this->m_flagPoleVector.push_back(this->m_flagPoleTop);
				this->m_flagPoleVector.back().setPosition(m_tilesPos.x - 50.f, m_tilesPos.y - 54.f);
				this->m_tilesPos.x += 96.f;
				break;
			case 'F': //FLAG POLE
				this->m_flagPoleVector.push_back(this->m_flagPole);
				this->m_flagPoleVector.back().setPosition(m_tilesPos.x + 40.f, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case 'G': //GOOMBAS
				this->m_goombaVector.push_back(new Goomba(this->m_goombaTexture, 6.f, this->m_goombaFrame));
				this->m_goombaVector.back()->setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case 'S': //SPIKIES
				this->m_spikieVector.push_back(new Spikie(this->m_spikieTexture, 6.f, this->m_spikieFrame));
				this->m_spikieVector.back()->setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case 'P': //PIRANHAS
				this->m_piranhaPlantVector.push_back(new PiranhaPlant());
				this->m_piranhaPlantVector.back()->setPosition(m_tilesPos.x, m_tilesPos.y - 48.f);
				this->m_tilesPos.x += 96.f;
				break;
			case 'C': //CLOUDS
				this->m_noCollisionVector.push_back(this->m_cloud);
				this->m_noCollisionVector.back().setPosition(m_tilesPos.x, m_tilesPos.y);
				this->m_tilesPos.x += 96.f;
				break;
			case 'B': //MINIMOUNTAINS
				this->m_noCollisionVector.push_back(this->m_bush);
				this->m_noCollisionVector.back().setPosition(m_tilesPos.x, m_tilesPos.y - 18.f);
				this->m_tilesPos.x += 96.f;
				break;
			}
		}
		this->m_worldFile.close();
		this->m_flagPoleVectorSize = this->m_flagPoleVector.size();
		this->m_noCollisionVectorSize = this->m_noCollisionVector.size();
		this->m_tilesVectorSize = this->m_tilesVector.size();
		this->m_goombaVectorSize = this->m_goombaVector.size();
		this->m_spikieVectorSize = this->m_spikieVector.size();
		this->m_coinsVectorSize = this->m_coinsVector.size();
		this->m_piranhaPlantVectorSize = this->m_piranhaPlantVector.size();
		this->m_isWorldBuilt = true;
		std::cout << "Vector size: " << this->m_tilesVector.size() << std::endl;
	}
	else
	{
		std::cerr << "\nERROR::WORLD::READWORLD: COULD NOT READ FILE\n";
	}
}

void World::initTilesSprites()
{
	if (!this->m_tileSet.loadFromFile("../data/TileSets/tileSetMario.png"))
		std::cout << "ERROR::Could not load player sprite sheet" << "\n";
	this->m_floor.setTexture(this->m_tileSet);
	this->m_floor.setTextureRect(sf::IntRect(0, 0, 16, 16));
	this->m_floor.setScale(6.f, 6.f);

	this->m_slab.setTexture(this->m_tileSet);
	this->m_slab.setTextureRect(sf::IntRect(48, 0, 16, 16));
	this->m_slab.setScale(6.f, 6.f);

	this->m_bricks.setTexture(this->m_tileSet);
	this->m_bricks.setTextureRect(sf::IntRect(16, 0, 16, 16));
	this->m_bricks.setScale(6.f, 6.f);

	this->m_questionBlock.setTexture(this->m_tileSet);
	this->m_questionBlock.setTextureRect(sf::IntRect(32, 0, 16, 16));
	this->m_questionBlock.setScale(6.f, 6.f);

	this->m_pipeTopLeft.setTexture(this->m_tileSet);
	this->m_pipeTopLeft.setTextureRect(sf::IntRect(0, 16, 16, 16));
	this->m_pipeTopLeft.setScale(6.f, 6.f);

	this->m_pipeTopRight.setTexture(this->m_tileSet);
	this->m_pipeTopRight.setTextureRect(sf::IntRect(16, 16, 16, 16));
	this->m_pipeTopRight.setScale(6.f, 6.f);

	this->m_pipeBottomLeft.setTexture(this->m_tileSet);
	this->m_pipeBottomLeft.setTextureRect(sf::IntRect(32, 16, 16, 16));
	this->m_pipeBottomLeft.setScale(6.f, 6.f);

	this->m_pipeBottomRight.setTexture(this->m_tileSet);
	this->m_pipeBottomRight.setTextureRect(sf::IntRect(48, 16, 16, 16));
	this->m_pipeBottomRight.setScale(6.f, 6.f);

	this->m_cloud.setTexture(this->m_tileSet);
	this->m_cloud.setTextureRect(sf::IntRect(0, 40, 48, 24));
	this->m_cloud.setScale(6.f, 6.f);

	this->m_bush.setTexture(this->m_tileSet);
	this->m_bush.setTextureRect(sf::IntRect(48, 45, 48, 19));
	this->m_bush.setScale(6.f, 6.f);

	this->m_flagPoleTop.setTexture(this->m_tileSet);
	this->m_flagPoleTop.setTextureRect(sf::IntRect(64, 0, 20, 25));
	this->m_flagPoleTop.setScale(6.f, 6.f);

	this->m_flagPole.setTexture(this->m_tileSet);
	this->m_flagPole.setTextureRect(sf::IntRect(94, 0, 2, 16));
	this->m_flagPole.setScale(6.f, 6.f);
}

void World::initEnemies()
{
	if (!this->m_goombaTexture.loadFromFile("../data/SpriteSheets/Enemies/goombaSpriteSheet.png"))
		std::cout << "ERROR::Could not load goomba sprite sheet" << "\n";
	this->m_goombaFrame = sf::IntRect(0, 0, 16, 16);

	if (!this->m_spikieTexture.loadFromFile("../data/SpriteSheets/Enemies/spikieSpriteSheet.png"))
		std::cout << "ERROR::Could not load spikie sprite sheet" << "\n";
	this->m_spikieFrame = sf::IntRect(0, 0, 16, 16);

}
