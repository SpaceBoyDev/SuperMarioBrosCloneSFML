#pragma once

#include <iostream>
#include <string>
#include <sstream>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

class UIManager
{
public:
	UIManager();
	virtual ~UIManager();

	//GETTERS & SETTERS
	const sf::Text getText() const { return this->m_text; }

	void setTextPosition(const float x, const float y) { this->m_text.setPosition(x, y); }
	void updateText(const int n, const bool win);

private:
	sf::Font m_font;
	sf::Text m_text;

	void initFont();
	void initText();

};