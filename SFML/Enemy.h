#pragma once
#include "Entity.h"
class Player;

class Enemy : public Entity
{
public:
	Enemy(sf::Texture& texture);

	void Update(float dt, MapReader& mr, Player& player);
	void Reset();

	void SetKilledState(bool killed)	{ m_Killed = killed; }
	int GetPointsGranted()				{ return m_PointsGranted; }

private:
	void Stop();
	void DetectPlayerCollision(Player& player);
	void DetectCollisionR(MapReader& mr, sf::FloatRect boundingBox, int index);
	void DetectCollisionL(MapReader& mr, sf::FloatRect boundingBox, int index);

private:
	bool m_Killed;
	const int m_PointsGranted;
};

