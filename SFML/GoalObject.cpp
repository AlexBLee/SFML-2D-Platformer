#include "GoalObject.h"
#include "Player.h"
#include "Game.h"

GoalObject::GoalObject(Type type, sf::Texture& texture)
	: Object(type, texture)
{
	switch (type)
	{
		case(Type::FlagPole):
			SetUVRectLeft((int)Type::FlagPole);
			break;

		case(Type::FlagStart):
			SetUVRectLeft((int)Type::FlagStart);
			break;

		case(Type::Flag):
			SetUVRectLeft((int)Type::Flag);
			break;
	}
}

void GoalObject::DetectCollision(Player& player, Game& game)
{
	// enable checking for collision if the player is close enough
	if (abs(GetSprite().getPosition().x - player.GetPosition().x) < GetDetectDistance())
	{
		if (GetSprite().getGlobalBounds().intersects(player.GetBoundingBox()))
		{
			player.SetPosition(sf::Vector2f(128, 32));
			game.PlaySound("smb_world_clear.wav");
			game.SetWin(true);
		}
	}

}
