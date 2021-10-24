#include "Entity.h"

Entity::Entity ()
{
	static size_t entitycounter = 0;
	id = entitycounter++;
}


void Entity::Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime)
{
	spriteHandler->Draw (window);
	spriteHandler->Update (deltaTime);
}


void Entity::Move (float offsetX, float offsetY)
{
	spriteHandler->currentSprite.move (offsetX, offsetY);
	Moved ();
}


int Entity::GetX () const
{
	return int (spriteHandler->currentSprite.getPosition ().x);

}


int Entity::GetY () const
{
	return int (spriteHandler->currentSprite.getPosition ().y);
}


int Entity::GetLeft () const
{
	return GetX ();
}


int Entity::GetTop () const
{
	return GetY ();
}


int Entity::GetWidth () const
{
	return spriteHandler->currentSpriteSheet->width;
}


int Entity::GetHeight () const
{
	return spriteHandler->currentSpriteSheet->height;
}


bool Entity::NeedsToBeIndexUpdated () const
{
	return moved;
}


sf::Vector2f Entity::GetCenter () const
{
	return spriteHandler->currentSprite.getPosition () - spriteHandler->currentSprite.getOrigin ()
		+ sf::Vector2f (float (spriteHandler->currentSpriteSheet->width) / 2.f, float (spriteHandler->currentSpriteSheet->height) / 2.f);
}


sf::IntRect Entity::GetBoundingBox (int offsetX, int offsetY, int offsetW, int offsetH) const
{
	return sf::IntRect (GetX () + offsetX, GetY () + offsetY, GetWidth () + offsetW, GetHeight () + offsetH);
}


void Entity::Moved (bool b)
{
	moved = b;
}