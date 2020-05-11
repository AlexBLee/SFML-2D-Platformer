#pragma once
#include <SFML/Graphics.hpp>

class Menu
{
public:
	Menu(sf::RenderWindow& window, std::string input);
	void SetWinScreen();
	void SetGameOverScreen();
	void DrawMenu(sf::RenderWindow& window);

private:
	sf::Font m_Font;
	sf::RectangleShape m_BackgroundShape;
	sf::Text m_InfoText;
	sf::Text m_BottomText;
};

