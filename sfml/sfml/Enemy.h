#pragma once

#include "Entity.h"

class Enemy : public Entity
{
public:
	Enemy () = delete;
	virtual ~Enemy () {}
	Enemy (sf::Vector2f pos);
	Enemy (float x, float y);
	virtual void Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime) override;
	virtual void Move (float offsetX, float offsetY) override;
	void Init (sf::Vector2f pos);
	sf::Vector2f pos;
	Attributes attributes;

	virtual int GetX ()	const override;
	virtual int GetY ()	const override;
	virtual int GetLeft ()	const override;
	virtual int GetTop ()	const override;
};