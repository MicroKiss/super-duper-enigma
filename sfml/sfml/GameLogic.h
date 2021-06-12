#pragma once

#include "SpacialIndex.h"

enum class Input
{
	jump = sf::Keyboard::Key::Space,
	moveRight = sf::Keyboard::Key::D,
	moveLeft = sf::Keyboard::Key::A,
	attack = sf::Keyboard::Key::J,
	powerMove = sf::Keyboard::Key::K,
	pause = sf::Keyboard::Key::Escape,
};

class GameLogic
{
public:
	GameLogic () {
		entities = nullptr;
		inputs = nullptr;
		player = nullptr;
	};
	~GameLogic ();
	void Update (float deltaTime);
	void UpdatePlayer (Player *player, float deltaTime);
	void UpdateBullet (Bullet *bullet, float deltaTime);
	void UpdateEnemy (Enemy *enemy, float deltaTime);
	void UpdateEntity (Entity *e, float deltaTime);
	void UpdateEntities (float deltaTime);

	Entity *AddEntity (Entity *ent);
	void RemoveEntity (Entity *ent);
	void RemoveEntity (size_t id);
	bool IsPressed (Input button);


	void SetInputs (std::set<sf::Keyboard::Key> *inputsPointer);
	void SetEntities (std::list<Entity *> *entitiesPointer);
	Player *player;
private:
	SpacialIndex spacialIndex;
	std::list<Entity *> *entities;
	std::list<Entity *> entitiesToRemove;
	std::set<sf::Keyboard::Key> *inputs;

};

