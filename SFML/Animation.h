#pragma once
#include <SFML/Graphics.hpp>


class Animation
{
public:
	Animation(sf::Texture* texture, sf::Vector2u spritesheetSize, float switchTime);
	void Update(float dt);

	void ChangeAnimation(int row, int frameCount, bool loop);
	sf::IntRect GetRect() { return m_UvRect; }

private:
	sf::IntRect m_UvRect;
	sf::Vector2u m_FrameCount;
	sf::Vector2u m_CurrentFrame;

	float m_TotalTime;
	float m_SwitchTime;

	bool m_IsLooping;
	bool m_PlayAgain;
};

