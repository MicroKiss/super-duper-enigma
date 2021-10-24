#include "Player.h"

Player::Player (sf::Vector2f pos)
{
	attributes = {100, 100, 200, 400, 10, 1, 0, 0};
	type = EntityType::Player;
	lastDir = 1;
	lastAttack = 0;
	spriteHandler = std::shared_ptr<SpriteHandler> (new SpriteHandler);
	spriteHandler->LoadSpriteSheet ("idle_r", "assets/player/idle_r.png", 64, 64, 10);
	spriteHandler->LoadSpriteSheet ("idle_l", "assets/player/idle_l.png", 64, 64, 10);
	spriteHandler->LoadSpriteSheet ("run_r", "assets/player/run_r.png", 64, 64, 10);
	spriteHandler->LoadSpriteSheet ("run_l", "assets/player/run_l.png", 64, 64, 10);
	spriteHandler->LoadSpriteSheet ("jump_l", "assets/player/jump_l.png", 64, 64, 10, 0.1f, false);
	spriteHandler->LoadSpriteSheet ("jump_r", "assets/player/jump_r.png", 64, 64, 10, 0.1f, false);
	spriteHandler->SetSprite ("idle_r");
	spriteHandler->currentSprite.setPosition (pos);
}


int Player::GetX () const
{
	return Entity::GetX () + 10;
}


int Player::GetWidth () const
{
	return Entity::GetWidth () - 20;
}


bool Player::CanAttack ()
{
	return lastAttack <= 0;
}