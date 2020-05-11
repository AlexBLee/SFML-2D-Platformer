#include "Projectile.h"
#include "Entity.h"
#include "MapReader.h"
#include "Tile.h"
#include "Player.h"

Projectile::Projectile(sf::Vector2f pos, int direction, sf::Texture& texture)
	: m_Sprite(texture)
	, m_Velocity(sf::Vector2f(15.0f * direction, 0.0f))
	, m_Existing(true)
{
	// set origin to middle
	sf::FloatRect localBounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(localBounds.width / 2.0f, 0);

	m_Sprite.setPosition(pos);
}


void Projectile::Update(float dt, MapReader& mr, std::vector<Enemy>& entities, Player& player)
{
	m_Sprite.move(m_Velocity.x * dt, m_Velocity.y * dt);

	// right collision check
	DetectCollision(mr, (m_Sprite.getPosition().x / 32 + 1) * 32 + m_Sprite.getPosition().y / 32, entities, player);

	// left collision check
	DetectCollision(mr, (m_Sprite.getPosition().x / 32 - 1) * 32 + m_Sprite.getPosition().y / 32, entities, player);

}

void Projectile::Draw(sf::RenderWindow& window)
{
	if (m_Existing)
	{
		window.draw(m_Sprite);
	}
}

void Projectile::DetectCollision(MapReader& mr, int index, std::vector<Enemy>& entities, Player& player)
{
	// wall collision
	if (m_Sprite.getGlobalBounds().intersects(mr.GetTileMap()[index].collisionBox))
	{
		if (!mr.GetTileMap()[index].passable)
		{
			m_Existing = false;
		}
	}

	// enemy collision
	for (auto& enemy : entities)
	{
		if (m_Sprite.getGlobalBounds().intersects(enemy.GetBoundingBox()))
		{
			// moving the projectile before it hits the enemies collision box twice instead of once.
			m_Sprite.setPosition(64, 0);
			m_Existing = false;

			enemy.PlaySound("smb_kick.wav");
			enemy.SetKilledState(true);

			player.AddScore(enemy.GetPointsGranted());
		}
	}
}

