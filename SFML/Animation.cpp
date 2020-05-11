#include "Animation.h"
#include <iostream>

Animation::Animation(sf::Texture* texture, sf::Vector2u imageCount, float switchTime)
	: m_UvRect(0,0, 
		texture->getSize().x / float(imageCount.x), 
		texture->getSize().y / float(imageCount.y))
	, m_FrameCount(imageCount)
	, m_CurrentFrame(0,0)
	, m_TotalTime(0.0f)
	, m_SwitchTime(switchTime)
	, m_IsLooping(true)
	, m_PlayAgain(true)
{
}

void Animation::Update(float dt)
{
	if (m_PlayAgain)
	{
		m_TotalTime += dt;

		// iterate through animation
		if (m_TotalTime >= m_SwitchTime)
		{
			m_TotalTime -= m_SwitchTime;
			m_CurrentFrame.x++;
		}


		// if the animation ends, loop to beginning
		if (m_CurrentFrame.x >= m_FrameCount.x)
		{
			if (!m_IsLooping)
			{
				m_PlayAgain = false;
			}
			m_CurrentFrame.x = 0;
		}

		m_UvRect.left = m_CurrentFrame.x * m_UvRect.width;
		m_UvRect.top = m_CurrentFrame.y * m_UvRect.height;
	}
	
}

void Animation::ChangeAnimation(int row, int imageCountX, bool loop)
{
	if (m_CurrentFrame.y != row)
	{
		m_IsLooping = loop;
		m_CurrentFrame.x = 0;
		m_CurrentFrame.y = row;
		m_PlayAgain = true;
	}
	m_FrameCount.x = imageCountX;

}
