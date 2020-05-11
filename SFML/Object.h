#pragma once
#include <SFML/Graphics.hpp>

class Player;
class Game;

class Object
{
public:
	enum class Type { Apple, Star, FlagPole, FlagStart, Flag };
	Object(Type num, sf::Texture &texture);

	void SetTaken(bool taken)						{ m_Taken = taken; }
	void SetPosition(sf::Vector2f pos)				{ m_Sprite.setPosition(pos); }

	void DrawSprite(sf::RenderWindow& window);
	void DetectCollision(Player& player, Game& game);

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::IntRect m_UvRect;

	bool m_Taken;
	bool m_PointsObject;
	int m_ScoreGiven;

};

