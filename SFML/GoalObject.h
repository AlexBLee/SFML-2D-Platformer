#pragma once
#include "Object.h"

class GoalObject : public Object
{
public:
	GoalObject(Type type, sf::Texture& texture);

	void DetectCollision(Player& player, Game& game);

};

