#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "ObjectTypes.h"

class Player;
class Game;

class Object
{
public:
	Object(Type type, sf::Texture &texture);

	sf::Sprite GetSprite()							{ return m_Sprite; }
	float GetDetectDistance()						{ return m_DetectDistance; }

	void SetPosition(sf::Vector2f pos)				{ m_Sprite.setPosition(pos); }
	void SetTaken(bool taken)						{ m_Taken = taken; }
	void SetUVRectLeft(int number);

	void PlaySound(std::string input);

	void DrawSprite(sf::RenderWindow& window);
	virtual void DetectCollision(Player& player, Game& game);

private:
	sf::Texture m_Texture;
	int numOfTextures;

	sf::Sprite m_Sprite;
	sf::IntRect m_UvRect;

	bool m_Taken;
	float m_DetectDistance;

	sf::SoundBuffer m_Buffer;
	sf::Sound m_Sound;
};

