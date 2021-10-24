#pragma once

#include <map>
#include <list>
#include "Entity.h"
#include "MicroMath.h"


class SpacialIndex
{
public:
	SpacialIndex (int gridSize = 128);
	~SpacialIndex ();
	std::list<Entity*>* operator()(std::pair <int, int> coords);
	std::list<Entity*>* operator()(int n, int m);
	void Clear (const std::list<Entity*>& entitiesToRemove);
	bool DoEntityNeedsToBeUpdated (Entity* ent);
	void CreateIndex (std::list<Entity*>* entities);
	Entity* CheckCollision (Entity* ent, EntityType typeId);
	Entity* CheckCollision (const sf::IntRect& rect, EntityType typeId);
	Entity* CheckCollision (float x, float y, float w, float h, EntityType typeId);
	std::list<Entity*> Query (const sf::IntRect& rect);
	std::list<Entity*> Query (Entity* ent);
	bool DoEntitiesIntersect (Entity* ent1, Entity* ent2);
private:
	int gridSize;
	std::map<std::pair<int, int>, std::list<Entity*> > index;
};

