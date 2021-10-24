#pragma once

#include <cassert>
#include <memory>
#include "SpacialIndex.h"
#include "Player.h"
#include "Enemy.h"
#include "Wall.h"

class GameLogic
{
public:
	GameLogic ()
	{
		entities = nullptr;
		inputs = nullptr;
	};
	~GameLogic ();
	void Update (float deltaTime);
	void UpdatePlayer (Player* player, float deltaTime);
	void UpdateBullet (Bullet* bullet, float deltaTime);
	void UpdateEnemy (Enemy* enemy, float deltaTime);
	void UpdateEntity (Entity* e, float deltaTime);
	void UpdateEntities (float deltaTime);

	Entity* AddEntity (Entity* ent);
	void RemoveEntity (Entity* ent);
	void RemoveEntity (size_t id);
	bool IsPressed (int button);

	void SetInputs (std::set<sf::Keyboard::Key>* inputsPointer);
	void SetEntities (std::list<Entity*>* entitiesPointer);

	std::shared_ptr<Player> player1;
	std::shared_ptr<Player> player2;
private:
	SpacialIndex spacialIndex;
	std::list<Entity*>* entities;
	std::list<Entity*> entitiesToRemove;
	std::shared_ptr<std::set<sf::Keyboard::Key>> inputs;

};

