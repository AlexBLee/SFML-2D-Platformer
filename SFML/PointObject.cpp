#include "PointObject.h"
#include "Player.h"

PointObject::PointObject(Type type, sf::Texture& texture)
	: Object(type, texture)
	, m_ScoreGiven(0)
	, m_Taken(false)
{
	switch (type)
	{
		case(Type::Apple):
			m_ScoreGiven = 300;
			break;

		case(Type::Star):
			m_ScoreGiven = 1000;
			break;
	}
}

void PointObject::DetectCollision(Player& player, Game& game)
{
	if (GetSprite().getGlobalBounds().intersects(player.GetBoundingBox()))
	{
		SetPosition(sf::Vector2f(0, 0)); // hide it at end of the map so player can no longer interact with it
		player.AddScore(m_ScoreGiven);
		player.PlaySound("smb_coin.wav");
		m_Taken = true;
	}
	
}
