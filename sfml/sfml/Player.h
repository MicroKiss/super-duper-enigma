#pragma once

#include "Entity.h"
#include "Bullet.h"

class Controls
{
public:
	int attack;
	int moveRight;
	int moveUp;
	int moveLeft;
	int moveDown;
	int powerMove;
	int pause;
};

class Player : public Entity
{
public:
	Player (sf::Vector2f pos);
	virtual ~Player () {};
	short lastDir;
	float lastAttack;
	virtual int GetX () const override;
	virtual int GetWidth ()const override;

	bool CanAttack ();
public:
	float vsp = 0;
	float hsp = 0;
	Attributes attributes;
	Controls controls;
	std::list<std::shared_ptr <AttributeModifier>> buffs;
};