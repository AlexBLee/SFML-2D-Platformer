#include <SFML/Graphics.hpp>
#pragma once

class Tile : sf::Vertex
{
public:
	Tile()
		: type(0)
		, passable(false)
		, killTile(false)
		, tile()
		, collisionBox()
	{
	}

	int type;
	bool passable;
	bool killTile;
	sf::Vertex tile;
	sf::FloatRect collisionBox;
};

