#include "Bullet.h"


Bullet::Bullet (sf::Vector2f pos, short direction)
{
	Init (pos, direction);
}


Bullet::Bullet (float x, float y, short direction)
{
	Init (sf::Vector2f (x, y), direction);
}


void Bullet::Move (float offsetX, float offsetY)
{
	pos.x += offsetX;
	pos.y += offsetY;
	Moved ();
}


void Bullet::Init (sf::Vector2f pos, short direction)
{
	this->pos = pos;
	startPos = pos;
	this->direction = direction;
	type = EntityType::Bullet;
	spriteHandler = std::shared_ptr<SpriteHandler> (new SpriteHandler);
	spriteHandler->LoadSpriteSheet ("idle", "assets/bullet.png", 10, 10, 1);
	spriteHandler->SetSprite ("idle");
}


void Bullet::Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}


int Bullet::GetX () const
{
	return static_cast<int> (pos.x);
}


int Bullet::GetY () const
{
	return static_cast<int> (pos.y);
}


int Bullet::GetLeft () const
{
	return GetX ();
}


int Bullet::GetTop () const
{
	return GetY ();
}
