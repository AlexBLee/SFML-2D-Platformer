#include "Entity.h"
#include "MapReader.h"

Entity::Entity(sf::Texture& texture)
	: m_Sprite(texture, sf::IntRect(0, 0, m_Width, m_Height))
	, m_Texture(texture)
	, m_Animation(&texture, sf::Vector2u(6, 4), 6.f)
	, m_Width(32)
	, m_Height(32)
	, m_SoundBuffer()
	, m_Sound()
	, m_Velocity(sf::Vector2f(0, 0))
	, m_Accel(0.1f)
	, m_deAccel(0.50f)
	, m_MaxLandSpeed(6.0f)
	, m_MaxJumpSpeed(6.0f)
	, m_inAir(true)
	, m_JumpForce(30.0f)
	, m_Gravity(3.0f)
	, m_PlatformAbove(false)
	, m_FaceRight(true)
	, moveRight(false)
	, moveLeft(false)
	, isJumping(false)
	, jumpAnimCheck(false)
	, idleFrameCount(4)
	, walkFrameCount(6)
	, jumpFrameCount(2)
	, hurtFrameCount(1)
{
	// load texture
	m_Sprite.setTexture(m_Texture, true);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, m_Width, m_Height));

	// center the pivot point
	sf::FloatRect localBounds = m_Sprite.getLocalBounds();
	m_Sprite.setOrigin(localBounds.width/2.0f, 0);

	// starting point
	m_Sprite.setPosition(15*32, 27*32);

	// set animation to idle
	m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);
}

void Entity::Update(float dt, MapReader& mr)
{
	CalculateCollision(mr);
	Move(dt);
	m_Sprite.move(m_Velocity.x * dt, m_Velocity.y * dt);

	// apply deacceleration
	if (m_Velocity.x > 0)
	{
		m_Velocity.x -= m_deAccel * dt;

		// stop velocity from bouncing around after getting close to 0
		if (m_Velocity.x <= 0)
		{
			m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);
			m_Velocity.x = 0;
		}
	}
	else if (m_Velocity.x < 0)
	{
		m_Velocity.x += m_deAccel * dt;

		// stop velocity from bouncing around after getting close to 0
		if (m_Velocity.x >= 0)
		{
			m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);
			m_Velocity.x = 0;
		}
	}

	// apply gravity
	if (m_inAir)
	{
		m_Animation.ChangeAnimation(animStates::Jump, jumpFrameCount, false);
		m_Velocity.y += (m_Gravity * dt);
	}
	else if (!m_inAir)
	{
		if (jumpAnimCheck)
		{
			m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);
			jumpAnimCheck = false;
		}
		m_Velocity.y = 0;
	}

	m_Animation.Update(dt);
	SetTextureRect(m_Animation.GetRect());

}

void Entity::DrawSprite(sf::RenderWindow& window)
{
	window.draw(m_Sprite);
}

void Entity::PlaySound(std::string input)
{
	m_SoundBuffer.loadFromFile(input);
	m_Sound.setBuffer(m_SoundBuffer);
	m_Sound.play();
}

void Entity::CalculateCollision(MapReader& mr)
{
	sf::FloatRect boundingBox = m_Sprite.getGlobalBounds();

	int xCoor = m_Sprite.getPosition().x / m_Width;
	int yCoor = m_Sprite.getPosition().y / m_Height;

	// below
	DetectCollisionB(mr, boundingBox, xCoor * m_Width + (yCoor + 1));

	// above
	DetectCollisionA(mr, boundingBox, xCoor * m_Width + (yCoor - 1));

	// right
	DetectCollisionR(mr, boundingBox, (xCoor + 1) * m_Width + yCoor);

	// left
	DetectCollisionL(mr, boundingBox, (xCoor - 1) * m_Width + yCoor);

}

void Entity::Move(float dt)
{
	if (moveLeft)
	{
		m_Animation.ChangeAnimation(animStates::Run, walkFrameCount, true);

		// if facing right, turn left
		if (m_FaceRight)
		{
			m_Sprite.scale(-1.f, 1.f);
			m_FaceRight = false;
		}

		m_Velocity.x -= m_Accel;

		if (m_Velocity.x < -m_MaxLandSpeed)
		{
			m_Velocity.x = -m_MaxLandSpeed;
		}
	}
	else if (moveRight)
	{
		m_Animation.ChangeAnimation(animStates::Run, walkFrameCount, true);

		// if facing left, turn right
		if (!m_FaceRight)
		{
			m_Sprite.scale(-1.f, 1.f);
			m_FaceRight = true;
		}

		m_Velocity.x += m_Accel;

		if (m_Velocity.x > m_MaxLandSpeed)
		{
			m_Velocity.x = m_MaxLandSpeed;
		}
	}

	if (isJumping)
	{
		jumpAnimCheck = true;

		if (!m_inAir)
		{
			m_Animation.ChangeAnimation(animStates::Jump, jumpFrameCount, false);

			PlaySound("smb_jump-small.wav");

			m_Velocity.y -= m_JumpForce;
			m_inAir = true;
		}
	}
}

void Entity::SetAnimationTexture(sf::Texture* texture, sf::Vector2u dimensions, int switchTime)
{
	m_Animation = Animation(texture, dimensions, switchTime);
}

void Entity::DetectCollisionL(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(mr.GetTileMap()[index].collisionBox))
	{
		if (!mr.GetTileMap()[index].passable)
		{
			m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);

			m_Sprite.setPosition(mr.GetTileMap()[index].tile.position.x + m_Width + boundingBox.width / 2 , m_Sprite.getPosition().y);
			m_Velocity.x = 0;
		}
	}
}

void Entity::DetectCollisionR(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	if (boundingBox.intersects(mr.GetTileMap()[index].collisionBox))
	{
		if (!mr.GetTileMap()[index].passable)
		{
			m_Animation.ChangeAnimation(animStates::Idle, idleFrameCount, true);

			m_Sprite.setPosition(mr.GetTileMap()[index].tile.position.x - boundingBox.width / 2, m_Sprite.getPosition().y);
			m_Velocity.x = 0;

		}
	}
}

void Entity::DetectCollisionB(MapReader &mr, sf::FloatRect boundingBox, int index)
{
	if (!mr.GetTileMap()[index].passable)
	{
		m_Sprite.setPosition(m_Sprite.getPosition().x, mr.GetTileMap()[index].tile.position.y - m_Sprite.getLocalBounds().height);
		m_inAir = false;
		m_PlatformAbove = false;
	}
	else
	{
		m_inAir = true;
	}

}

void Entity::DetectCollisionA(MapReader& mr, sf::FloatRect boundingBox, int index)
{
	if (!mr.GetTileMap()[index].passable)
	{
		if (!m_PlatformAbove)
		{
			m_Sprite.setPosition(m_Sprite.getPosition().x, mr.GetTileMap()[index].tile.position.y + m_Sprite.getLocalBounds().height);
			m_Velocity.y = 0;
			m_PlatformAbove = true;
		}
	}

}








