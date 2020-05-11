#include "MapReader.h"
#include "Tile.h"

MapReader::MapReader(std::string textFile)
	: m_TileMap({})
	, mlevelFile()
	, level("")
	, m_vertices()
	, m_tileset()
	, m_levelWidth(192)
	, m_levelHeight(32)
	, m_TileHeight(32)
	, m_TileWidth(32)
	, m_PlayerSpawnPosition()
	, m_ObjectPositions()
{
	LoadFile(textFile);
}

void MapReader::LoadFile(std::string textFile)
{   
    // Opening file
    mlevelFile.open(textFile);

    if (mlevelFile.is_open())
    {
		// Get each character and write it to a string that will become the level.
		char c;
        while(mlevelFile.get(c))
        {
			if (c != '\n')
			{
				level += c;
			}
        }
    }
	
	mlevelFile.close();
	SetLevel();
}

// Adapted from : 
// https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
sf::VertexArray MapReader::SetLevel()
{
	// setting texture
	m_tileset.loadFromFile("spritesheet.png");

	// Size the vertex array to fit all the quads into the array.
	m_vertices.setPrimitiveType(sf::Quads);
	m_vertices.resize(m_levelWidth * m_levelHeight * 4);

	for (int i = 0; i < m_levelWidth; i++)
	{
		for (int j = 0; j < m_levelHeight; j++)
		{
			// get the number/symbol representing the texture from the level string.
			int tileNumber = level[i + j * m_levelWidth] - '0';

			// if the mapreader hits these numbers, set player/object/enemy spawn points instead of setting a specific texture
			// from the spritesheet.
			// the tileNumber then changes to 2 to put the sky texture in.

			switch (tileNumber)
			{
				case 4:
					m_PlayerSpawnPosition = sf::Vector2f(i * m_TileWidth, j * m_TileHeight);
					tileNumber = 2;
					break;
				case 5:
					m_ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * m_TileWidth, j * m_TileHeight), Object::Type::Apple));
					tileNumber = 2;
					break;
				case 6:
					m_ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * m_TileWidth, j * m_TileHeight), Object::Type::Star));
					tileNumber = 2;
					break;
				case 7:
					m_ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * m_TileWidth, j * m_TileHeight), Object::Type::FlagPole));
					tileNumber = 2;
					break;
				case 8:
					m_ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * m_TileWidth, j * m_TileHeight), Object::Type::FlagStart));
					tileNumber = 2;
					break;
				case 9:
					m_ObjectPositions.push_back(ObjectPos(sf::Vector2f(i * m_TileWidth, j * m_TileHeight), Object::Type::Flag));
					tileNumber = 2;
					break;
				case 72:
					m_EnemySpawnPositions.push_back(sf::Vector2f(i * m_TileWidth, j * m_TileHeight));
					tileNumber = 2;
					break;
			}

				

			// find the texture based off tileNumber in the tileset texture
			int tu = tileNumber % (m_tileset.getSize().x / m_TileWidth);
			int tv = tileNumber / (m_tileset.getSize().x / m_TileWidth);

			// Pointer to the current tile's quad
 			sf::Vertex* quad = &m_vertices[(i + j * m_levelWidth) * 4];

			// define its 4 corners
			quad[0].position = sf::Vector2f(i * m_TileWidth, j * m_TileHeight);
			quad[1].position = sf::Vector2f((i + 1) * m_TileWidth, j * m_TileHeight);
			quad[2].position = sf::Vector2f((i + 1) * m_TileWidth, (j + 1) * m_TileHeight);
			quad[3].position = sf::Vector2f(i * m_TileWidth, (j + 1) * m_TileHeight);

			// define its 4 texture coordinates
			quad[0].texCoords = sf::Vector2f(tu * m_TileWidth, tv * m_TileHeight);
			quad[1].texCoords = sf::Vector2f((tu + 1) * m_TileWidth, tv * m_TileHeight);
			quad[2].texCoords = sf::Vector2f((tu + 1) * m_TileWidth, (tv + 1) * m_TileHeight);
			quad[3].texCoords = sf::Vector2f(tu * m_TileWidth, (tv + 1) * m_TileHeight);

			Tile tile;
			tile.tile = *quad;
			tile.type = tileNumber;

			tile.collisionBox = sf::FloatRect(tile.tile.position.x, tile.tile.position.y, m_TileWidth, m_TileHeight);

			if (tile.type == 0 || tile.type == 1)
			{
				tile.passable = false;
			}
			else if (tile.type == 3)
			{
				tile.passable = true;
				tile.killTile = true;
			}
			else
			{
				tile.passable = true;
			}

			m_TileMap.push_back(tile);

		}

	}
	return m_vertices;
}

// Adapted from : 
// https://www.sfml-dev.org/tutorials/2.4/graphics-vertex-array.php
void MapReader::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = &m_tileset;

	// draw the vertex array
	target.draw(m_vertices, states);
}

