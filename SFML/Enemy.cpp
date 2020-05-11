#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(sf::Texture& texture)
	: Entity(texture)
	, m_Killed(false)
	, m_PointsGranted(300)
{
	SetTexture(texture);
	moveRight = true;
	moveLeft = false;
}

void Enemy::Update(float dt, MapReader& mr, Player& player)
{
	Entity::Update(dt, mr);
	DetectPlayerCollision(player);

	// hide the enemies in a corner so no longer interactable
	if (m_Killed)
	{
		// the enemy is placed underground:
		// reason:	if placed in the upper corner, it still builds y velocity due to gravity.
		//			when it respawns, it will pass through the ground due to it being too fast.
		SetPosition(sf::Vector2f(32, 30 * 32));
		Stop();
	}
}

void Enemy::Stop()
{
	moveLeft = false;
	moveRight = false;
}

void Enemy::Reset()
{
	moveLeft = false;
	moveRight = true;
	m_Killed = false;
}

void Enemy::DetectCollisionR(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(mr.GetTileMap()[index].collisionBox))
	{
		if (!mr.GetTileMap()[index].passable || mr.GetTileMap()[index].killTile)
		{
			moveRight = false;
			moveLeft = true;
		}
	}
}

void Enemy::DetectCollisionL(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(mr.GetTileMap()[index].collisionBox))
	{
		if (!mr.GetTileMap()[index].passable || mr.GetTileMap()[index].killTile)
		{
			moveRight = true;
			moveLeft = false;
		}
	}
}

void Enemy::DetectPlayerCollision(Player& player)
{
	if (GetBoundingBox().intersects(player.GetBoundingBox()))
	{
		player.SubtractLife();
	}
}
