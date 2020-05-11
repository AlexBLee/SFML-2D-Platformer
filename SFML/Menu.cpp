#include "Menu.h"

Menu::Menu(sf::RenderWindow& window, std::string input)
	: m_Font()
	, m_BackgroundShape()
	, m_InfoText()
	, m_BottomText()
{
	// make background black
	m_BackgroundShape.setFillColor(sf::Color(0, 0, 0, 255));
	m_BackgroundShape.setSize(window.getView().getSize() * 1.1f);

	// put the texts in appropriate spots
	m_InfoText.setPosition((window.getView().getSize().x / 3.f),
		(window.getView().getSize().y / 3.f));

	m_BottomText.setPosition((window.getView().getSize().x / 6.f),
		(window.getView().getSize().y / 2.f));

	m_Font.loadFromFile(input);
	m_InfoText.setFont(m_Font);
	m_BottomText.setFont(m_Font);
}


void Menu::SetWinScreen()
{
	m_InfoText.setString("Congratulations");
	m_BottomText.setString("Press enter to try again!");
}

void Menu::SetGameOverScreen()
{
	m_InfoText.setString("Game Over");
	m_BottomText.setString("Press enter to try again!");
}

void Menu::DrawMenu(sf::RenderWindow& window)
{
	window.draw(m_BackgroundShape);
	window.draw(m_InfoText);
	window.draw(m_BottomText);
}
