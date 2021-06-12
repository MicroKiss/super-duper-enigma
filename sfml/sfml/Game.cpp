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
	gameLogic.AddEntity (new Player (sf::Vector2f (128*2, window->getSize ().y / 2.f)));

	for (size_t i = 0; i < 1366/64; ++i)
		gameLogic.AddEntity (new Wall (sf::Vector2f (64*i, window->getSize ().y / 2.f + 300)));
	
	gameLogic.AddEntity (new Wall (sf::Vector2f (128, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*2, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*2, window->getSize ().y / 2.f + 300-64*2)));
	gameLogic.AddEntity (new Wall (sf::Vector2f (128*3, window->getSize ().y / 2.f + 300-64)));
	gameLogic.AddEntity (new Enemy (sf::Vector2f (128*6, window->getSize ().y / 2.f + 300-64)));

}

void Game::KeyDown (Input button)
{
	inputs.insert (static_cast<sf::Keyboard::Key> (button));
}


void Game::HandleJoystickButtonPressed (unsigned int buttonCode)
{
	switch (buttonCode)
	{
	case 0: //A
		KeyDown (Input::jump);
		break;
	case 1: //B
		KeyDown (Input::powerMove);
		break;
	case 2: //X
		KeyDown (Input::attack);
		break;
	case 3: //Y
		KeyDown (Input::pause);
		paused = !paused;
		break;
	default:
		break;
	}
}

void Game::HandleJoystickButtonReleased (unsigned int buttonCode)
{
	switch (buttonCode)
	{
	case 0: //A
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::jump));
		break;
	case 1: //B
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::powerMove));
		break;
	case 2: //X
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::attack));
		break;
	case 3: //Y
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::pause));
		break;
	default:
		break;
	}
}

void Game::HandleJoystickMove (sf::Joystick::Axis axis, float position)
{
	switch (axis)
	{
	case sf::Joystick::X:
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::moveLeft));
		inputs.erase (static_cast<sf::Keyboard::Key> (Input::moveRight));
		if (position < -30.f)
			KeyDown (Input::moveLeft);
		else if (position > 30.f)
			KeyDown (Input::moveRight);
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
	while (window->pollEvent (event)) {
		switch (event.type) {
		case sf::Event::KeyPressed:
			inputs.insert (event.key.code);
			if (event.key.code == static_cast<sf::Keyboard::Key> (Input::pause))
				paused = !paused;
			break;
		case sf::Event::JoystickButtonPressed:
			//std::cout << "joystick button pressed!" << std::endl;
			//std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
			HandleJoystickButtonPressed (event.joystickButton.button);
			break;
		case sf::Event::JoystickButtonReleased:
			//std::cout << "joystick button pressed!" << std::endl;
			//std::cout << "joystick id: " << event.joystickButton.joystickId << std::endl;
			HandleJoystickButtonReleased (event.joystickButton.button);
			break;
		case sf::Event::JoystickMoved:
			HandleJoystickMove (event.joystickMove.axis, event.joystickMove.position);
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

