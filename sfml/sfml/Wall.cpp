#include "Wall.h"

Wall::Wall (sf::Vector2f pos)
{
	Init (pos);
}


Wall::Wall (float x, float y)
{
	Init (sf::Vector2f (x, y));
}


void Wall::Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}


void Wall::Init (sf::Vector2f pos)
{
	this->pos = pos;
	type = EntityType::Wall;
	spriteHandler = std::shared_ptr<SpriteHandler> (new SpriteHandler);
	spriteHandler->LoadSpriteSheet ("idle", "assets/wall.png", 64, 64, 1);
	spriteHandler->SetSprite ("idle");
}


int Wall::GetX () const
{
	return static_cast<int> (pos.x);
}


int Wall::GetY () const
{
	return static_cast<int> (pos.y);
}


int Wall::GetLeft () const
{
	return GetX ();
}


int Wall::GetTop () const
{
	return GetY ();
}
