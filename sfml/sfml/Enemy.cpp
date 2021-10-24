#include "Enemy.h"

Enemy::Enemy (sf::Vector2f pos)
{
	Init (pos);
}


Enemy::Enemy (float x, float y)
{
	Init (sf::Vector2f (x, y));
}


void Enemy::Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}


void Enemy::Move (float offsetX, float offsetY)
{
	pos.x += offsetX;
	pos.y += offsetY;
	Moved ();
}


void Enemy::Init (sf::Vector2f pos)
{
	this->pos = pos;
	type = EntityType::Enemy;
	spriteHandler = std::shared_ptr<SpriteHandler> (new SpriteHandler);
	spriteHandler->LoadSpriteSheet ("idle", "assets/enemy.png", 48, 64, 1);
	spriteHandler->SetSprite ("idle");
	attributes = {100,100, 200, 400, 10, 1, 0, 0};
}


int Enemy::GetX () const
{
	return static_cast<int> (pos.x);
}


int Enemy::GetY () const
{
	return static_cast<int> (pos.y);
}


int Enemy::GetLeft () const
{
	return GetX ();
}


int Enemy::GetTop () const
{
	return GetY ();
}
