#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MapReader.h"
#include "Tile.h"
#include "Animation.h"
#include <iostream>

class MapReader;
class Animation;

class Entity
{
public:
	Entity(sf::Texture& texture);

	void Update(float dt, MapReader& mr);
	void DrawSprite(sf::RenderWindow& window);
	void PlaySound(std::string input);

	sf::Sprite GetSprite()					{ return m_Sprite; }

	sf::Vector2f GetPosition()				{ return m_Sprite.getPosition(); }
	void SetPosition(sf::Vector2f position) { m_Sprite.setPosition(position); }

	sf::FloatRect GetBoundingBox()			{ return m_Sprite.getGlobalBounds(); }

	void SetTextureRect(sf::IntRect ir)		{ m_Sprite.setTextureRect(ir); }
	void SetTexture(sf::Texture& texture)	{ m_Sprite.setTexture(texture); }

private:
	void CalculateCollision(MapReader& mr);
	void Move(float dt);

protected:
	virtual void DetectCollisionR(MapReader& mr, sf::FloatRect boundingBox, int index);
	virtual void DetectCollisionL(MapReader& mr, sf::FloatRect boundingBox, int index);
	virtual void DetectCollisionB(MapReader& mr, sf::FloatRect boundingBox, int index);
	void DetectCollisionA(MapReader& mr, sf::FloatRect boundingBox, int index);
	void SetAnimationTexture(sf::Texture* texture, sf::Vector2u dimensions, int switchTime);




private:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

	Animation m_Animation;
	enum animStates { Idle, Run, Jump, Hurt };

	const int m_Width;
	const int m_Height;

	sf::SoundBuffer m_SoundBuffer;
	sf::Sound m_Sound;

	sf::Vector2f m_Velocity;
	float m_Accel;
	float m_deAccel;

	const float m_MaxLandSpeed;
	const float m_MaxJumpSpeed;

	bool m_inAir;
	float m_JumpForce;

	const float m_Gravity;

	bool m_PlatformAbove;
	bool m_FaceRight;

protected:
	bool moveRight;
	bool moveLeft;
	bool isJumping;
	bool jumpAnimCheck; // needed for animation checking

	int idleFrameCount;
	int walkFrameCount;
	int jumpFrameCount;
	int hurtFrameCount;

};

