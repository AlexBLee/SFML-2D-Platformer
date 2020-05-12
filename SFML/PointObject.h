#pragma once
#include "Object.h"

class PointObject : public Object
{
public:
	PointObject(Type type, sf::Texture& texture);
	void DetectCollision(Player& player, Game& game);

private:
	int m_ScoreGiven;
	bool m_Taken;

};

