#include "Entity.h"

Entity::Entity () {
	static size_t entitycounter = 0;
	id = entitycounter++;
	spriteHandler = nullptr;
}


void Entity::Draw (sf::RenderWindow *const window, float deltaTime) {
	spriteHandler->Draw (window);
	spriteHandler->Update (deltaTime);
}

void Entity::Move (float offsetX, float offsetY)
{
	spriteHandler->currentSprite.move (offsetX, offsetY);
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

sf::Vector2f Entity::GetCenter () const
{
	return spriteHandler->currentSprite.getPosition () - spriteHandler->currentSprite.getOrigin ()
		+ sf::Vector2f (float (spriteHandler->currentSpriteSheet->width) / 2.f, float (spriteHandler->currentSpriteSheet->height) / 2.f);
}

sf::IntRect Entity::GetBoundingBox (int offsetX, int offsetY, int offsetW, int offsetH) const
{
	return sf::IntRect (GetX () + offsetX, GetY () + offsetY, GetWidth () + offsetW, GetHeight () + offsetH);
}

Player::Player (sf::Vector2f pos)
{
	attributes = {100, 100, 200, 400, 10, 1, 0, 0};
	type = EntityType::Player;
	lastDir = 1;
	lastAttack = 0;
	spriteHandler = new SpriteHandler;
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
	return Entity::GetX () +10;
}

int Player::GetWidth () const
{
	return Entity::GetWidth() -10;
}

bool Player::CanAttack ()
{
	return lastAttack <= 0;
}


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

}

void Bullet::Init (sf::Vector2f pos, short direction)
{
	this->pos = pos;
	startPos = pos;
	this->direction = direction;
	type = EntityType::Bullet;
	spriteHandler = SingletonBulletSpriteHandler::GetSpriteHandler ();
}


void Bullet::Draw (sf::RenderWindow *const window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}

int Bullet::GetX () const
{
	return pos.x;
}

int Bullet::GetY () const
{
	return pos.y;
}

int Bullet::GetLeft () const
{
	return GetX ();
}

int Bullet::GetTop () const
{
	return GetY ();
}


Wall::Wall (sf::Vector2f pos)
{
	Init (pos);
}



Wall::Wall (float x, float y)
{
	Init (sf::Vector2f (x, y));
}

void Wall::Draw (sf::RenderWindow *const window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}



void Wall::Init (sf::Vector2f pos)
{
	this->pos = pos;
	type = EntityType::Wall;
	spriteHandler = SingletonWallSpriteHandler::GetSpriteHandler ();
}

int Wall::GetX () const
{
	return pos.x;
}

int Wall::GetY () const
{
	return pos.y;
}

int Wall::GetLeft () const
{
	return GetX ();
}

int Wall::GetTop () const
{
	return GetY ();
}

Enemy::Enemy (sf::Vector2f pos)
{
	Init (pos);
}

Enemy::Enemy (float x, float y)
{
	Init (sf::Vector2f (x, y));
}

void Enemy::Draw (sf::RenderWindow *const window, float deltaTime)
{
	spriteHandler->currentSprite.setPosition (pos);
	spriteHandler->Draw (window);
}

void Enemy::Move (float offsetX, float offsetY)
{
	pos.x += offsetX;
	pos.y += offsetY;
}

void Enemy::Init (sf::Vector2f pos)
{
	this->pos = pos;
	type = EntityType::Enemy;
	spriteHandler = SingletonEnemySpriteHandler::GetSpriteHandler ();
	attributes = {100,100, 200, 400, 10, 1, 0, 0};

}

int Enemy::GetX () const
{
	return pos.x;
}

int Enemy::GetY () const
{
	return pos.y;
}

int Enemy::GetLeft () const
{
	return GetX ();
}

int Enemy::GetTop () const
{
	return GetY ();
}
