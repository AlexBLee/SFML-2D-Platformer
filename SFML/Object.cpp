#include "Object.h"
#include "Player.h"
#include "Game.h"

Object::Object(Type type, sf::Texture& texture)
	: m_Texture(texture)
	, numOfTextures(5)
	, m_Sprite(texture)
	, m_UvRect(0, 0, m_Texture.getSize().x/numOfTextures, m_Texture.getSize().y)
	, m_Taken(false)
{
}

void Object::SetUVRectLeft(int number)
{
	m_UvRect.left = m_UvRect.width * number; 
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

