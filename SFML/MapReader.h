#pragma once
#include <SFML/Graphics.hpp>
#include "Object.h"
#include "ObjectTypes.h"
#include <iostream>
#include <fstream>
#include <string>

class Tile;

struct ObjectPos
{
	sf::Vector2f position;
	Type pType;

	ObjectPos(sf::Vector2f pos, Type type)
		: position(pos)
		, pType(type)
	{
	}
};


class MapReader : public sf::Transformable, public sf::Drawable
{
public:
	MapReader(std::string textFile);

	std::vector<Tile>			&GetTileMap()				{ return m_TileMap; }
	std::vector<ObjectPos>		&GetObjectSpawnPositions()	{ return m_ObjectPositions; }
	std::vector<sf::Vector2f>	&GetEnemySpawnPositions()	{ return m_EnemySpawnPositions; }
	sf::Vector2f				&GetPlayerSpawnPosition()	{ return m_PlayerSpawnPosition; }

	int GetTileWidth()	{ return m_TileWidth; }
	int GetTileHeight() { return m_TileHeight; }

private:
	void LoadFile(std::string textFile);
	sf::VertexArray SetLevel();
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	std::ifstream mlevelFile;
	std::string level;

	sf::VertexArray m_vertices;
	sf::Texture m_tileset;

	const int m_levelWidth;
	const int m_levelHeight;
	
	const int m_TileHeight;
	const int m_TileWidth;

	std::vector<Tile> m_TileMap;
	std::vector<ObjectPos> m_ObjectPositions;
	sf::Vector2f m_PlayerSpawnPosition;
	std::vector<sf::Vector2f> m_EnemySpawnPositions;

};

