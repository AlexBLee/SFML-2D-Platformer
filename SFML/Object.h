#pragma once
#include <SFML/Graphics.hpp>

class Player;
class Game;

class Object
{
public:
	enum class Type { Apple = 0, Star, FlagPole, FlagStart, Flag };
	Object(Type type, sf::Texture &texture);

	sf::Sprite GetSprite()							{ return m_Sprite; }
	void SetPosition(sf::Vector2f pos)				{ m_Sprite.setPosition(pos); }
	void SetTaken(bool taken)						{ m_Taken = taken; }

	void DrawSprite(sf::RenderWindow& window);
	virtual void DetectCollision(Player& player, Game& game);

private:
	sf::Texture m_Texture;
	sf::Sprite m_Sprite;
	sf::IntRect m_UvRect;
	bool m_Taken;
};

