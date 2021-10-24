#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include <list>
#include <memory>
#include "GameLogic.h"




class Game
{

public:
	Game ();
	virtual ~Game ();
	void Update ();
	void Draw ();
	void Exit ();
	bool IsAlive () const { return alive; }
private:
	void Init ();
	void HandleEvents ();
	void HandleJoystickButtonPressed (unsigned int buttonCode, const Controls& controls);
	void HandleJoystickButtonReleased (unsigned int buttonCode, const Controls& controls);
	void HandleJoystickMove (sf::Joystick::Axis axis, float position, const Controls& controls);
	void DrawPauseMenu();


private:
	sf::Clock clock;
	float deltaTime;
	void KeyDown (int button);
	bool alive;
	sf::RenderWindow *window;
	std::set<sf::Keyboard::Key> inputs;
	std::list<Entity *> entities;

	GameLogic gameLogic;
	bool paused = false;

};