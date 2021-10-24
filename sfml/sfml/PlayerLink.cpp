#include "PlayerLink.h"

PlayerLink::PlayerLink (std::shared_ptr<Player> p1, std::shared_ptr<Player> p2)
{
	player1 = p1;
	player2 = p2;
	type = EntityType::PlayerLink;
}

void PlayerLink::Draw (std::shared_ptr<sf::RenderWindow> window, float deltaTime)
{

	sf::Vertex vertices[] =
	{
	sf::Vertex (player1->GetCenter (), sf::Color::Red),
	sf::Vertex (player2->GetCenter (), sf::Color::Blue)
	};

	window->draw (vertices, 2, sf::LinesStrip);
}

int PlayerLink::GetX () const
{
	return 0;
}

int PlayerLink::GetY () const
{
	return 0;
}

int PlayerLink::GetLeft () const
{
	return 0;
}

int PlayerLink::GetTop () const
{
	return 0;
}

int PlayerLink::GetWidth () const
{
	return 0;
}

int PlayerLink::GetHeight () const
{
	return 0;
}
