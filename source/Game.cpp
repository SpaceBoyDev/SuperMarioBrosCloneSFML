#include "Game.h"

//Constructors //Destructors
Game::Game()
{
	this->initVariables();
    this->initPlayer();
	this->initWindow();
    this->initWorld();
    this->initUIManager();
}

Game::~Game()
{
    delete this->m_player;
    delete this->m_world;
}

//Getters & Setters
//-->IS GAME RUNNING?<--
const bool Game::running() const
{
	return this->m_window.isOpen();
}
const bool Game::getEndGame() const
{
    return this->m_endGame;
}
//-->PUBLIC FUNCTIONS<---
//-->UPDATE<---
void Game::update()
{
    pollEvents();
    //this->updateInputs();
    this->updateView();
    if (!this->m_endGame)
    {
        this->updateDeltaTime();
        this->updatePlayer();
        this->updatePlayerCollision();
        this->updateEnemies();
    }

    if (this->m_reInit)
    {
        this->reInit(4.f);
    }
}
//-->RENDER<---
void Game::render() //Renders the game objects and updates the window
{
    this->m_window.clear(sf::Color(92, 148, 252));

    this->renderWorld();
    this->renderPlayer();
    this->renderUIManager(this->m_window);

    this->m_window.display();
}
//-->POLL EVENTS<--
void Game::pollEvents()
{
    //Event polling
    while (this->m_window.pollEvent(this->m_ev))
    {
        switch (this->m_ev.type)
        {
        case sf::Event::Closed:
            this->m_window.close();
            break;
        case sf::Event::KeyPressed:
            if (this->m_ev.key.code == sf::Keyboard::Escape)
                this->m_window.close();
            break;
        }
    }
}
//-->reINIT<--
void Game::reInit(const float timeToWait)
{
    if (this->m_restartCrono)
    {
        this->m_crono.restart();
        this->m_restartCrono = false;
    }

    if (this->m_crono.getElapsedTime().asSeconds() > timeToWait)
    {
        this->m_world->reInit();
        this->m_player->reInit();
        this->updateUIManager(this->m_player->getCoins());
        this->m_restartCrono = true;
        this->m_reInit = false;
    }
}

//-->PRIVATE FUNCTIONS<--
//-->DELTATIME<---
void Game::updateDeltaTime()
{
    this->m_deltaTime = this->m_deltaClock.restart();
}
bool Game::isInView(sf::FloatRect sprite)
{
    sf::Vector2f viewCenter(this->m_view.getCenter());
    sf::Vector2f viewSize(this->m_view.getSize());

    sf::FloatRect currentViewRect(viewCenter - viewSize / 2.f, viewSize);

    return (sprite.intersects(currentViewRect));
}
//INIT FUNCTIONS
void Game::initVariables()
{

    //Game logic
    this->m_endGame = false;
    this->m_reInit = false;
    this->m_restartCrono = true;
}

void Game::initWindow()
{
    this->m_view.reset(sf::FloatRect(this->m_player->getPlayerPos().x, this->m_player->getPlayerPos().y, 1920.f, 1080.f));
    this->m_window.create(sf::VideoMode(1920, 1080), "PlatformProj", sf::Style::Close | sf::Style::Titlebar);
    this->m_window.setFramerateLimit(60);
}

void Game::updateView()
{
    sf::Vector2f movement = sf::Vector2f((this->m_player->getPlayerPos().x - this->m_view.getCenter().x), (this->m_player->getPlayerPos().y - this->m_view.getCenter().y));

    //this->m_view.move(0.f, (movement.y * 50.f) * this->getDelta());
    this->m_view.move((movement.x * 50.f) * this->getDelta(), 0.f);

    if (this->m_view.getCenter().x <= 960)
    {
        this->m_view.setCenter((962), this->m_view.getCenter().y);
    }

    if (this->m_view.getCenter().y >= 490)
    {
        this->m_view.setCenter(this->m_view.getCenter().x, 489);
    }
    this->m_window.setView(m_view);
}

void Game::winGame()
{
    this->m_player->setCanMove(false);
    this->m_UIManager->updateText(this->m_player->getCoins(), true);
}

//-->PLAYER FUNCTIONS<---
void Game::renderPlayer()
{
    this->m_player->render(this->m_window);
}

void Game::updatePlayer()
{
    this->m_player->update();
}

void Game::initPlayer()
{
    this->m_player = new Player();
}

void Game::updatePlayerCollision()
{
    ///COLLISIONS
    for (size_t i = 0; i < this->m_world->getTilesVectorSize(); i++)
    {
        if (this->isInView(this->m_world->getTiles()[i].getGlobalBounds()))
        {
            //TILE COLLISIONS
            if ((this->m_player->getGlobalBoundsColliderJump().intersects(this->m_world->getTiles()[i].getGlobalBounds())))
            {
                if (this->m_world->getTiles()[i].getPosition().y > this->m_player->getGlobalBoundsCollider().top + 30.f)
                {
                    this->m_player->setPosition(this->m_player->getGlobalBoundsCollider().left, this->m_world->getTiles()[i].getGlobalBounds().top -
                        this->m_player->getGlobalBoundsCollider().height - this->m_player->getGlobalBoundsColliderJump().height - 30.f);
                    this->m_player->resetVelocityY();
                    this->m_player->setIsGrounded(true);
                }
            }

            if (this->m_player->getGlobalBoundsColliderHead().intersects(this->m_world->getTiles()[i].getGlobalBounds()))
            {
                this->m_player->setPosition(this->m_player->getGlobalBoundsCollider().left, this->m_world->getTiles()[i].getGlobalBounds().top + this->m_world->getTiles()[i].getGlobalBounds().height + 25.f);
                this->m_player->resetVelocityY();
                std::cout << "chimpun \n";
            }


            if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getTiles()[i].getGlobalBounds()))
            {
                if (this->m_player->getGlobalBoundsCollider().left < this->m_world->getTiles()[i].getGlobalBounds().left)
                {
                    this->m_player->setPosition(this->m_world->getTiles()[i].getPosition().x - this->m_player->getGlobalBoundsCollider().width - 1.f, this->m_player->getGlobalBoundsCollider().top);
                    this->m_player->resetVelocityX();
                    std::cout << "\nhacia derecha\n";
                }
                else if (this->m_player->getGlobalBoundsCollider().left > this->m_world->getTiles()[i].getGlobalBounds().left)
                {
                    this->m_player->setPosition(this->m_world->getTiles()[i].getGlobalBounds().left + this->m_world->getTiles()[i].getGlobalBounds().width + 1.f, this->m_player->getGlobalBoundsCollider().top);
                    this->m_player->resetVelocityX();
                    std::cout << "\nhacia izquierda\n";
                }
            }
        }
    }

        //ENEMIES COLLISIONS
    if (this->m_player->getIsAlive())
    {
        //GOOMBA COLLISIONS
        for (size_t j = 0; j < this->m_world->getGoombaVectorSize(); j++)
        {
            if (this->isInView(this->m_world->getGoombas()[j]->getGlobalBounds()) && this->m_world->getGoombas()[j]->getIsAlive())
            {
                //JUMP
                if ((this->m_player->getGlobalBoundsColliderJump().intersects(this->m_world->getGoombas()[j]->getGlobalBoundsCollider()))
                    && this->m_world->getGoombas()[j]->getPosition().y > this->m_player->getGlobalBoundsCollider().top && (this->m_player->getIsFalling()))
                {
                    //this->m_world->getGoombas()[i]->~Goomba();

                    this->m_world->deleteGoomba(j);
                    this->m_player->bounceJump();
                    break;
                    std::cout << "\nGOOMBA PISADO\n";

                }
                //PLAYER GETS HIT
                if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getGoombas()[j]->getGlobalBoundsCollider()))
                {

                    this->m_player->setCanMove(false);
                    this->m_player->setIsAlive(false);
                    //this->reInit(5.f);
                    this->m_reInit = true;

                    std::cout << "\nPLAYER HIT\n";
                }
            }
        }
        //SPIKIE COLLISIONS
        for (size_t j = 0; j < this->m_world->getSpikieVectorSize(); j++)
        {
            if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getSpikies()[j]->getGlobalBoundsCollider()))
            {

                this->m_player->setCanMove(false);
                this->m_player->setIsAlive(false);
                //this->reInit(5.f);
                this->m_reInit = true;

                std::cout << "\nPLAYER HIT\n";
            }
        }
        //PIRANHA PLANT COLLISIONS
        for (size_t j = 0; j < this->m_world->getPiranhaPlantVectorSize(); j++)
        {
            if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getPiranhaPlants()[j]->getGlobalBounds()))
            {

                this->m_player->setCanMove(false);
                this->m_player->setIsAlive(false);
                //this->reInit(5.f);
                this->m_reInit = true;

                std::cout << "\nPLAYER HIT\n";
            }
        }
        //COINS COLLISIONS
        for (size_t j = 0; j < this->m_world->getCoinsVectorSize(); j++)
        {
            if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getCoins()[j]->getGlobalBounds()))
            {

                this->m_player->addCoins(1);
                this->updateUIManager(this->m_player->getCoins());
                this->m_world->deleteCoin(j);
                std::cout << "\nPLAYER HIT\n";
            }
        }

        //FLAG POLE COLLISIONS
        for (size_t j = 0; j < this->m_world->getFlagPoleVectorSize(); j++)
        {
            if (this->m_player->getGlobalBoundsCollider().intersects(this->m_world->getFlagPole()[j].getGlobalBounds()))
            {
                this->winGame();
                this->m_player->move(3.f, 0.f);
                this->m_reInit = true;
                std::cout << "\nWin\n";
            }
        }
    }

    if (this->m_player->getPlayerPos().x < 0)
    {
        this->m_player->setPosition(1.f, this->m_player->getPlayerPos().y); 
    }

    if (this->m_player->getPlayerPos().y > 1080)
    {
        this->m_player->setCanMove(false);
        this->m_player->setIsAlive(false);
        //this->reInit(5.f);
        this->m_reInit = true;
    }
}


//-->WORLD FUNCTIONS<--
void Game::renderWorld()
{
    this->m_world->render(this->m_window);
}

void Game::initWorld()
{
    this->m_world = new World();
}

//-->ENEMIES FUNCTIONS<--
void Game::updateEnemies()
{
    this->m_world->update();
    this->enemiesCollisions();
}

void Game::enemiesCollisions()
{
    for (size_t i = 0; i < this->m_world->getTilesVectorSize(); i++)
    {
        //GOOMBA COLLISIONS
        for (size_t j = 0; j < this->m_world->getGoombaVectorSize(); j++)
        {
            if (this->m_world->getGoombas()[j]->getStartMovement())
            {

                if (this->m_world->getGoombas()[j]->getGlobalBoundsCollider().intersects(this->m_world->getTiles()[i].getGlobalBounds()))
                {
                    if (this->m_world->getGoombas()[j]->getGlobalBoundsCollider().left < this->m_world->getTiles()[i].getGlobalBounds().left)
                    {
                        this->m_world->getGoombas()[j]->setPosition(this->m_world->getTiles()[i].getPosition().x - this->m_world->getGoombas()[j]->getGlobalBounds().width - 1.f,
                            this->m_world->getGoombas()[j]->getPosition().y);
                        this->m_world->getGoombas()[j]->changeDirection();
                        std::cout << "\nGOOMBA IZQUIERDA\n";
                    }
                    else if (this->m_world->getGoombas()[j]->getGlobalBounds().left > this->m_world->getTiles()[i].getGlobalBounds().left)
                    {
                        this->m_world->getGoombas()[j]->setPosition(this->m_world->getTiles()[i].getGlobalBounds().left + this->m_world->getTiles()[i].getGlobalBounds().width + 1.f, this->m_world->getGoombas()[j]->getGlobalBounds().top);
                        this->m_world->getGoombas()[j]->changeDirection();
                        std::cout << "\nGOOMBA DERECHA\n";
                    }
                }
            }
            //CHECKS IF THE GOOMBA IS INSIDE THE VIEW. IF IT IS, IT STARTS MOVING
            if (this->isInView(this->m_world->getGoombas()[j]->getGlobalBounds()))
            {
                this->m_world->getGoombas()[j]->setStartMovement(true);
            }
        }

        //SPIKIE COLLISIONS
        for (size_t j = 0; j < this->m_world->getSpikieVectorSize(); j++)
        {
            if (this->m_world->getSpikies()[j]->getStartMovement())
            {
                if (this->m_world->getSpikies()[j]->getGlobalBoundsCollider().intersects(this->m_world->getTiles()[i].getGlobalBounds()))
                {
                    if (this->m_world->getSpikies()[j]->getGlobalBoundsCollider().left < this->m_world->getTiles()[i].getGlobalBounds().left)
                    {
                        this->m_world->getSpikies()[j]->setPosition(this->m_world->getTiles()[i].getPosition().x - this->m_world->getSpikies()[j]->getGlobalBounds().width - 1.f,
                            this->m_world->getSpikies()[j]->getPosition().y);
                        this->m_world->getSpikies()[j]->changeDirection();
                        std::cout << "\nGOOMBA IZQUIERDA\n";
                    }
                    else if (this->m_world->getSpikies()[j]->getGlobalBounds().left > this->m_world->getTiles()[i].getGlobalBounds().left)
                    {
                        this->m_world->getSpikies()[j]->setPosition(this->m_world->getTiles()[i].getGlobalBounds().left + this->m_world->getTiles()[i].getGlobalBounds().width + 1.f, this->m_world->getSpikies()[j]->getGlobalBounds().top);
                        this->m_world->getSpikies()[j]->changeDirection();
                        std::cout << "\nGOOMBA DERECHA\n";
                    }
                }
            }

            //CHECKS IF THE SPIKIE IS INSIDE THE VIEW. IF IT IS, IT STARTS MOVING
            if (this->isInView(this->m_world->getSpikies()[j]->getGlobalBounds()))
            {
                this->m_world->getSpikies()[j]->setStartMovement(true);
            }
        }

    }
}


//UIMANGER FUNCTIONS
void Game::initUIManager()
{
    this->m_UIManager = new UIManager();
}

void Game::updateUIManager(const int n)
{
    this->m_UIManager->updateText(this->m_player->getCoins(), false);
}

void Game::renderUIManager(sf::RenderTarget& target)
{
    this->m_UIManager->setTextPosition(m_view.getCenter().x - 920.f, m_view.getCenter().y - 500.f);
    target.draw(this->m_UIManager->getText());
}


