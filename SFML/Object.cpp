#include "Object.h"
#include "Player.h"
#include "Game.h"

Object::Object(Type type, sf::Texture& texture)
	: m_Texture(texture)
	, m_Sprite(texture)
	, m_UvRect(0, 0, m_Texture.getSize().x/5, m_Texture.getSize().y)
	, m_Taken(false)
	, m_PointsObject(true)
	, m_ScoreGiven(300)
{
	// scrolling through sprite sheet and choosing the correct object
	switch (type)
	{
		case(Type::Apple):
			m_UvRect.left = 0;
			m_ScoreGiven = 300;
			break;

		case(Type::Star):
			m_UvRect.left = m_UvRect.width;
			m_ScoreGiven = 1000;
			break;

		case(Type::FlagPole):
			m_UvRect.left = m_UvRect.width * 2;
			m_PointsObject = false;
			break;

		case(Type::FlagStart):
			m_UvRect.left = m_UvRect.width * 3;
			m_PointsObject = false;
			break;

		case(Type::Flag):
			m_UvRect.left = m_UvRect.width * 4;
			m_PointsObject = false;
			break;
	}
	m_Sprite.setTextureRect(m_UvRect);

}

void Object::DrawSprite(sf::RenderWindow& window)
{
	if (!m_Taken)
	{
		window.draw(m_Sprite);
	}
}

void Object::DetectCollision(Player& player, Game& game)
{
	if (m_Sprite.getGlobalBounds().intersects(player.GetBoundingBox()))
	{
		if (m_PointsObject)
		{
			m_Sprite.setPosition(0, 0); // hide it at end of the map so player can no longer interact with it
			player.AddScore(m_ScoreGiven);
			player.PlaySound("smb_coin.wav");
			m_Taken = true;
		}
		else
		{
			player.SetPosition(sf::Vector2f(128, 32));
			game.PlaySound("smb_world_clear.wav");
			game.SetWin(true);
		}

	}
}
