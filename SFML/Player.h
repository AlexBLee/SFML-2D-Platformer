#pragma once
#include "Entity.h"
#include "Projectile.h"
#include <queue>

class Game;

class Player : public Entity
{
public:
	Player(sf::Texture& texture);
	void Update(float dt, MapReader& mr);

	int GetLives()								{ return m_Lives; }
	void SetLives(int lives)					{ m_Lives = lives; }
	
	int GetScore()								{ return m_Score; }
	void SetScore(int score)					{ m_Score = score; m_ScoreChanged = true; }
	void AddScore(int score)					{ m_Score += score; m_ScoreChanged = true; }

	bool LivesChanged()							{ return m_LivesChanged; }
	bool ScoreChanged()							{ return m_ScoreChanged; }

	void SetLivesChanged(bool changed)			{ m_LivesChanged = changed; }
	void SetScoreChanged(bool changed)			{ m_ScoreChanged = changed; }

	std::deque<Projectile> &GetProjectiles()	{ return m_Projectiles; }
	
	void Reset();
	void SubtractLife();

private:
	void DetectCollisionB(MapReader& mr, sf::FloatRect boundingBox, int index);

private:
	bool m_Dead;
	int m_Lives;
	int m_Score;

	bool m_LivesChanged; // needed for avoiding constant calls to to_string every frame
	bool m_ScoreChanged;

	std::deque<Projectile> m_Projectiles;
	sf::Texture m_ProjectileTexture;

	float m_ShootCooldown;
	sf::Clock m_CooldownClock;


};

