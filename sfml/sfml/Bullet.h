#pragma once

#include "Entity.h"

class Bullet : public Entity
{
public:
	Bullet () = delete;
	Bullet (sf::Vector2f pos, short direction);
	Bullet (float x, float y, short direction);
	~Bullet () {};
	virtual void Move (float offsetX, float offsetY) override;
	void Init (sf::Vector2f pos, short direction);
	virtual void Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime) override;

	short direction;
	sf::Vector2f startPos;
	sf::Vector2f pos;
	int speed = 700;


	virtual int GetX () const override;
	virtual int GetY () const override;
	virtual int GetLeft () const override;
	virtual int GetTop () const override;
};