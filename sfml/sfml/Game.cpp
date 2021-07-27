#include "Game.h"
#include <iostream>
#pragma warning (disable : 26812 )

Game::Game ()
{
	window = new sf::RenderWindow (sf::VideoMode (1366, 768), "Micro Game!");
	window->setVerticalSyncEnabled (true);
	alive = true;
	gameLogic.SetInputs (&inputs);
	gameLogic.SetEntities (&entities);
	paused = false;
	Init ();
}

Game::~Game ()
{
	delete window;
}

void Game::Update ()
{
	HandleEvents ();

	deltaTime = clock.restart ().asSeconds ();
	if (!paused)
	{
		gameLogic.Update (deltaTime);
	}
}

void Game::Exit () {
	alive = false;
	// we could write a save function here
}

void Game::Draw ()
{
	window->clear (sf::Color::Yellow);

	if (!paused)
	{

		for (auto &entity : entities)
			entity->Draw (window, deltaTime);
	}
	else {
		sf::Font font;
		font.loadFromFile ("assets/Dale Adventure.ttf");
		sf::Text text;
		text.setFont (font);
		text.setString ("PAUSED");
		text.setCharacterSize (100);
		text.setFillColor (sf::Color::Red);
		text.setStyle (sf::Text::Bold | sf::Text::Underlined);
		text.setPosition (window->getSize ().x / 2.f, window->getSize ().y / 2.f);
		window->draw (text);
	}
	//draw ui
	window->display ();
}

void Game::Init ()
{
	{
		Entity* entity = gameLogic.AddEntity (new Player (sf::Vector2f (128*2, window->getSize ().y / 2.f)));
		Player* player = static_cast<Player*> (entity);
		player->controls.moveUp = sf::Keyboard::Key::W;
		player->controls.moveLeft = sf::Keyboard::Key::A;
		player->controls.moveDown = sf::Keyboard::Key::S;
		player->controls.moveRight = sf::Keyboard::Key::D;
		player->controls.attack = sf::Keyboard::Key::J;
		player->controls.powerMove = sf::Keyboard::Key::K;
		player->controls.pause = sf::Keyboard::Key::Escape;
	}
	{
		Entity* entity = gameLogic.AddEntity (new Player (sf::Vector2f (128 * 3, window->getSize ().y / 2.f)));
		Player* player = static_cast<Player*> (entity);
		player->controls.moveUp = sf::Keyboard::Key::Up;
		player->controls.moveLeft = sf::Keyboard::Key::Left;
		player->controls.moveDown = sf::Keyboard::Key::Down;
		player->controls.moveRight = sf::Keyboard::Key::Right;
		player->controls.attack = sf::Keyboard::Key::Numpad1;
		player->controls.powerMove = sf::Keyboard::Key::Numpad2;
		player->controls.pause = sf::Keyboard::Key::Escape;
	}


	for (size_t i = 0; i < 1366/64; ++i)
		gameLogic.AddEntity (new Wall (sf::Vector2f (64*i, window->getSize ().y / 2.f + 300)));
	
	gameLogic.AddEntity (new Wall (sf::Vector2f (128, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*2, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*2, window->getSize ().y / 2.f + 300-64*2)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*3, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Enemy (sf::Vector2f (128*6, window->getSize ().y / 2.f + 300-64)));

}

void Game::KeyDown (int button)
{
	inputs.insert (static_cast<sf::Keyboard::Key> (button));
}


void Game::HandleJoystickButtonPressed (unsigned int buttonCode, const Controls& controls)
{
	switch (buttonCode)
	{
	case 0: //A
		KeyDown (controls.moveUp);
		break;
	case 1: //B
		KeyDown (controls.powerMove);
		break;
	case 2: //X
		KeyDown (controls.attack);
		break;
	case 3: //Y
		KeyDown (controls.pause);
		paused = !paused;
		break;
	default:
		break;
	}
}

void Game::HandleJoystickButtonReleased (unsigned int buttonCode, const Controls& controls)
{
	switch (buttonCode)
	{
	case 0: //A
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.moveUp));
		break;
	case 1: //B
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.powerMove));
		break;
	case 2: //X
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.attack));
		break;
	case 3: //Y
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.pause));
		break;
	default:
		break;
	}
}

void Game::HandleJoystickMove (sf::Joystick::Axis axis, float position, const Controls& controls)
{
	switch (axis)
	{
	case sf::Joystick::X:
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.moveLeft));
		inputs.erase (static_cast<sf::Keyboard::Key> (controls.moveRight));
		if (position < -30.f)
			KeyDown (controls.moveLeft);
		else if (position > 30.f)
			KeyDown (controls.moveRight);
		break;
	case sf::Joystick::Y:
		break;
	default:
		break;
	}
}


void Game::HandleEvents ()
{
	static sf::Event event;
	static Controls controls;
	while (window->pollEvent (event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			inputs.insert (event.key.code);
			if (event.key.code == static_cast<sf::Keyboard::Key> (sf::Keyboard::Key::Escape))
				paused = !paused;
			break;
		case sf::Event::JoystickButtonPressed:
			controls = event.joystickButton.joystickId == 0 ? gameLogic.player1->controls : gameLogic.player2->controls;
			HandleJoystickButtonPressed (event.joystickButton.button, controls);
			break;
		case sf::Event::JoystickButtonReleased:
			controls = event.joystickButton.joystickId == 0 ? gameLogic.player1->controls : gameLogic.player2->controls;
			HandleJoystickButtonReleased (event.joystickButton.button, controls);
			break;
		case sf::Event::JoystickMoved:
			controls = event.joystickMove.joystickId == 0 ? gameLogic.player1->controls : gameLogic.player2->controls;
			HandleJoystickMove (event.joystickMove.axis, event.joystickMove.position, controls);
			break;
		case sf::Event::KeyReleased:
			inputs.erase (event.key.code);
			break;
		case sf::Event::Closed:
			Exit ();
			window->close ();
			break;
		default:
			break;
		}
	}
}

