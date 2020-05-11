#include "Player.h"
#include "Game.h"
#include "Projectile.h"

Player::Player(sf::Texture& texture)
	: Entity(texture)
	, m_LivesChanged(false)
	, m_ScoreChanged(false)
	, m_Dead(false)
	, m_Lives(3)
	, m_Score(0)
	, m_Projectiles()
	, m_ProjectileTexture()
	, m_ShootCooldown(1.0f)
	, m_CooldownClock()
{
	m_ProjectileTexture.loadFromFile("bullet.png");
	m_CooldownClock.restart();
}

void Player::Update(float dt, MapReader& mr)
{
	// keyboard input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		moveLeft = true;
	}
	else
	{
		moveLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		moveRight = true;
	}
	else
	{
		moveRight = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		isJumping = true;
	}
	else
	{
		isJumping = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		// shoot projectile
		if (m_CooldownClock.getElapsedTime().asSeconds() >= m_ShootCooldown)
		{
			PlaySound("smb_fireball.wav");
			m_Projectiles.push_back(Projectile(GetPosition(), GetSprite().getScale().x, m_ProjectileTexture));
			m_CooldownClock.restart();
		}
	}

	Entity::Update(dt, mr);
}

void Player::Reset()
{
	SetLives(3);
	SetScore(0);
}

void Player::SubtractLife()
{
	if (!m_Dead)
	{
		SetScore(0);
		PlaySound("smb_mariodie.wav");
		m_Lives--;
		m_LivesChanged = true;
	}
}

void Player::DetectCollisionB(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	// detecting kill tiles
	Entity::DetectCollisionB(mr, boundingBox, index);
	if (mr.GetTileMap()[index].killTile)
	{
		SubtractLife();
	}
}

