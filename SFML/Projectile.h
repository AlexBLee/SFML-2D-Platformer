#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
class MapReader;
class Enemy;

class Projectile
{
public:
	Projectile(sf::Vector2f pos, int direction, sf::Texture& texture);

	void Update(float dt, MapReader& mr, std::vector<Enemy>& entities, Player& player);
	void Draw(sf::RenderWindow& window);

	bool isExisting() { return m_Existing; }

private:
	void DetectCollision(MapReader& mr, int index, std::vector<Enemy>& entities, Player& player);

private:
	sf::Sprite m_Sprite;
	const sf::Vector2f m_Velocity;
	
	bool m_Existing;

};
