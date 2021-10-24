#pragma once

#include <set>
#include <list>
#include <iostream>
#include "SpriteHandler.h"

enum class EntityType
{
	Undefined = 0,
	Player,
	Bullet,
	Wall,
	Enemy
};


enum class Shape
{
	Rectangle = 0,
	Circle = 1,
};


struct Attributes
{
	float maxHealth;
	float health;
	float movSpeed;
	float jumpSpeed;
	float damage;
	float attackSpeed;
	float critChance;
	float dodgeChance;
};


class AttributeModifier
{
public:
	sf::Clock clock;
	sf::Time duration;
	virtual ~AttributeModifier () {};
	virtual void apply (Attributes& attributes) = 0;
	bool Expired () { return clock.getElapsedTime () > duration; }
};


class DoubleSpeedBuff : public AttributeModifier
{
public:
	DoubleSpeedBuff ()
	{
		duration = sf::seconds (5);
	};

	virtual void apply (Attributes& attributes) override
	{
		attributes.movSpeed *= 2;
		attributes.attackSpeed *= 10;
		attributes.jumpSpeed *= 1.3f;
	}
};


class Entity
{
public:
	Entity ();
	Entity (const Entity&) = delete;
	Entity& operator=(const Entity&) = delete;
	virtual ~Entity () {}
	virtual void Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime);
	virtual void Move (float offsetX, float offsetY);
	virtual int GetX ()const;
	virtual int GetY ()const;
	virtual int GetLeft ()const;
	virtual int GetTop ()const;
	virtual int GetWidth ()const;
	virtual int GetHeight ()const;
	virtual bool NeedsToBeIndexUpdated () const;
	virtual sf::Vector2f GetCenter () const;
	virtual sf::IntRect GetBoundingBox (int offsetX = 0, int offsetY = 0, int offsetW = 0, int offsetH = 0) const;
	size_t GetID ()const { return id; }
	void Moved (bool b = true);
public:
	std::shared_ptr<SpriteHandler> spriteHandler;
	EntityType type = EntityType::Undefined;
	Shape shape = Shape::Rectangle;
private:
	bool moved = true;
	size_t id;
};