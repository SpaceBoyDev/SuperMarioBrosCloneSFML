#include "UI/UIManager.h"

UIManager::UIManager()
{
	this->initFont();
	this->initText();
}

UIManager::~UIManager()
{

}

void UIManager::initFont()
{
	if (!this->m_font.loadFromFile("../data/Fonts/NESFont.ttf"))
		std::cout << "ERROR::Could not load font file" << "\n";
}

void UIManager::initText()
{
	this->m_text.setFont(this->m_font);
	this->m_text.setCharacterSize(30);
	this->m_text.setFillColor(sf::Color::White);
	this->m_text.setString("Coins: 0");
}

void UIManager::updateText(const int n, const bool win)
{
	std::stringstream ss;
	if (!win)
	{
		this->m_text.setCharacterSize(30);
		ss << "Coins: " << n;
		this->m_text.setString(ss.str());

	}
	else
	{
		ss << "YOU WIN\nCOINS: " << n;
		this->m_text.setCharacterSize(50);
		this->m_text.setPosition(this->m_text.getPosition().x + 920.f, this->m_text.getPosition().y + 500.f);
		this->m_text.setString(ss.str());
	}
}
