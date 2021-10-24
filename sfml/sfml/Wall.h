#pragma once

#include "Entity.h"

class Wall : public Entity
{
public:
	Wall () = delete;
	virtual ~Wall () {}
	Wall (sf::Vector2f pos);
	Wall (float x, float y);
	virtual void Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime) override;
	void Init (sf::Vector2f pos);
	sf::Vector2f pos;


	virtual int GetX ()	const override;
	virtual int GetY ()	const override;
	virtual int GetLeft ()	const override;
	virtual int GetTop ()	const override;
};