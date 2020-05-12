#include "Object.h"
#include "Player.h"
#include "Game.h"

Object::Object(Type type, sf::Texture& texture)
	: m_Texture(texture)
	, m_Sprite(texture)
	, m_UvRect(0, 0, m_Texture.getSize().x/5, m_Texture.getSize().y)
	, m_Taken(false)
{
	switch (type)
	{
		case(Type::Apple):
			m_UvRect.left = 0;
			break;

		case(Type::Star):
			m_UvRect.left = m_UvRect.width;
			break;
		
		case(Type::FlagPole):
			m_UvRect.left = m_UvRect.width * 2;
			break;

		case(Type::FlagStart):
			m_UvRect.left = m_UvRect.width * 3;
			break;

		case(Type::Flag):
			m_UvRect.left = m_UvRect.width * 4;
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
}

