#pragma once

#include "Entity.h"
#include "Player.h"

class PlayerLink : public Entity
{
public:
	PlayerLink () = delete;
	virtual ~PlayerLink () {};
	PlayerLink (std::shared_ptr<Player> p1, std::shared_ptr<Player> p2);
	virtual void Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime) override;

	virtual int GetX ()	const override;
	virtual int GetY ()	const override;
	virtual int GetLeft ()	const override;
	virtual int GetTop ()	const override;
	virtual int GetWidth ()	const override;
	virtual int GetHeight ()	const override;
	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
private:
};

