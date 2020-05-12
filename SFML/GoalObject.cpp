#include "GoalObject.h"
#include "Player.h"
#include "Game.h"

GoalObject::GoalObject(Type type, sf::Texture& texture)
	: Object(type, texture)
{
}

void GoalObject::DetectCollision(Player& player, Game& game)
{
	if (GetSprite().getGlobalBounds().intersects(player.GetBoundingBox()))
	{
		player.SetPosition(sf::Vector2f(128, 32));
		game.PlaySound("smb_world_clear.wav");
		game.SetWin(true);
	}

}
