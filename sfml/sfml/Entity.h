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
	Circle,
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
	virtual void apply (Attributes &attributes) = 0;
	bool Expired () { return clock.getElapsedTime () > duration; }
};

class DoubleSpeedBuff : public AttributeModifier
{
public:
	DoubleSpeedBuff () {
		duration = sf::seconds (5);
	};

	virtual void apply (Attributes &attributes) override
	{
		attributes.movSpeed *= 2;
		attributes.attackSpeed *= 10;
		attributes.jumpSpeed *= 1.3;
	}
};


class Entity
{
public:
	Entity ();
	Entity (const Entity &) = delete;
	Entity &operator=(const Entity &) = delete;
	virtual ~Entity () {}
	virtual void Draw (sf::RenderWindow *const window, float deltaTime);
	virtual void Move (float offsetX, float offsetY);
	virtual int GetX ()const;
	virtual int GetY ()const;
	virtual int GetLeft ()const;
	virtual int GetTop ()const;
	virtual int GetWidth ()const;
	virtual int GetHeight ()const;
	virtual sf::Vector2f GetCenter () const;
	virtual sf::IntRect GetBoundingBox (int offsetX = 0, int offsetY = 0, int offsetW = 0, int offsetH = 0) const;
	size_t GetID ()const { return id; }
public:
	SpriteHandler *spriteHandler;
	EntityType type = EntityType::Undefined;
	Shape shape = Shape::Rectangle;
private:
	size_t id;
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
	Attributes attributes;

	std::list<AttributeModifier *> buffs;
private:
};

class Bullet : public Entity
{
public:
	Bullet () = delete;
	Bullet (sf::Vector2f pos, short direction);
	Bullet (float x, float y, short direction);
	~Bullet () {};
	virtual void Move (float offsetX, float offsetY) override;
	void Init (sf::Vector2f pos, short direction);
	virtual void Draw (sf::RenderWindow *const window, float deltaTime) override;

	short direction;
	sf::Vector2f startPos;
	sf::Vector2f pos;
	int speed = 700;


	virtual int GetX	() const override;
	virtual int GetY	() const override;
	virtual int GetLeft () const override;
	virtual int GetTop	() const override;
};

class Wall : public Entity
{
public:
	Wall () = delete;
	virtual ~Wall () {}
	Wall (sf::Vector2f pos);
	Wall (float x, float y);
	virtual void Draw (sf::RenderWindow *const window, float deltaTime) override;
	void Init (sf::Vector2f pos);
	sf::Vector2f pos;


	virtual int GetX	()	const override;
	virtual int GetY	()	const override;
	virtual int GetLeft ()	const override;
	virtual int GetTop	()	const override;
};

class Enemy : public Entity
{
public:
	Enemy () = delete;
	virtual ~Enemy () {}
	Enemy (sf::Vector2f pos);
	Enemy (float x, float y);
	virtual void Draw (sf::RenderWindow *const window, float deltaTime) override;
	virtual void Move (float offsetX, float offsetY) override;
	void Init (sf::Vector2f pos);
	sf::Vector2f pos;
	Attributes attributes;

	virtual int GetX ()	const override;
	virtual int GetY ()	const override;
	virtual int GetLeft ()	const override;
	virtual int GetTop ()	const override;

};