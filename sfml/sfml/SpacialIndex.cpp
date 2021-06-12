#include "SpacialIndex.h"
#include <algorithm>


SpacialIndex::SpacialIndex () : gridSize(64)
{
}

SpacialIndex::~SpacialIndex ()
{
}

std::list<Entity *> *SpacialIndex::operator()(std::pair<int, int> coords)
{
	return &index.at (coords);
}

std::list<Entity *> *SpacialIndex::operator()(int n, int m)
{
	return this->operator()(std::pair<int, int> (n, m));
}


void SpacialIndex::Clear ()
{
	index.clear ();
}


void SpacialIndex::CreateIndex (std::list<Entity *> *entities, int gridSize /* = 8 */)
{
	this->gridSize = gridSize;
	for (auto &entity : *entities) {
		//entitás szélének meghatározása (cella szélek)
		int left = entity->GetX ();
		int top = entity->GetY ();
		int cellLeft = left / gridSize;
		int cellTop = top / gridSize;
		int cellRight = (left + entity->GetWidth ()) / gridSize;
		int cellBottom = (top + entity->GetHeight ()) / gridSize;

		for (int x = cellLeft; x < cellRight; ++x) {
			for (int y = cellTop; y < cellBottom; ++y) {
				auto &cellList = index[std::pair<int, int> (x, y)];
				cellList.push_back (entity);
			}
		}
	}
}



Entity* SpacialIndex::CheckCollision (Entity *ent, EntityType typeId)
{
	auto nearObjects = Query (ent);
	for (auto &object : nearObjects) {
		if (object != ent && object->type == typeId)
			return object;
	}
	return nullptr;
}


Entity* SpacialIndex::CheckCollision (const sf::IntRect &rect, EntityType typeId)
{
	auto nearObjects = Query (rect);
	for (auto &object : nearObjects) {
		if (object->type == typeId)
			return object;
	}
	return nullptr;
}


Entity *SpacialIndex::CheckCollision (float x, float y, float w, float h, EntityType typeId)
{
	return CheckCollision (sf::IntRect (x, y, w, h), typeId);
}


std::list<Entity *> SpacialIndex::Query (const sf::IntRect &rect)
{
	int left = rect.left;
	int top = rect.top;
	int cellLeft = left / gridSize;
	int cellTop = top / gridSize;
	int cellRight = (left + rect.width) / gridSize;
	int cellBottom = (top + rect.height) / gridSize;
	std::list<Entity *> result;

	for (int x = cellLeft; x < cellRight; ++x) {
		for (int y = cellTop; y < cellBottom; ++y) {
			if (index.contains (std::pair<int, int> (x, y))) {
				auto cellData = index[std::pair<int, int> (x, y)];
				for (auto &e : cellData) {
					//if(rect.intersects(e->spriteHandler->currentSprite.getGlobalBounds ()))
					if (/*e != ent &&*/ std::find (result.begin (), result.end (), e) == result.end ())
						result.push_back (e);
				}
			}
		}
	}
	return result;
}


std::list<Entity *> SpacialIndex::Query (Entity *ent)
{

	int left = ent->GetX ();
	int top = ent->GetY ();
	int cellLeft = left / gridSize;
	int cellTop = top / gridSize;
	int cellRight = (left + ent->GetWidth ()) / gridSize;
	int cellBottom = (top + ent->GetHeight ()) / gridSize;
	std::list<Entity *> result;

	for (int x = cellLeft; x < cellRight; ++x) {
		for (int y = cellTop; y < cellBottom; ++y) {
			if (index.contains (std::pair<int, int> (x, y))) {
				auto cellData = index[std::pair<int, int> (x, y)];
				for (auto &e : cellData) {
					if (DoEntitiesIntersect (ent, e) && std::find (result.begin (), result.end (), e) == result.end ())
						result.push_back (e);
				}
			}
		}
	}
	return result;
}

bool SpacialIndex::DoEntitiesIntersect (Entity *ent1, Entity *ent2)
{
	if (ent1 == ent2)
		return true;

	if (ent1->shape == ent2->shape) {
		if (ent1->shape == Shape::Rectangle)
			return RectangleIntersect (ent1->GetX (), ent1->GetY (), ent1->GetWidth (), ent1->GetHeight (), ent2->GetX (), ent2->GetY (), ent2->GetWidth (), ent2->GetHeight ());
			//return ent1->spriteHandler->currentSprite.getGlobalBounds ().intersects (ent2->spriteHandler->currentSprite.getGlobalBounds ());

	}
	return false;
}



/*
engine.place_meeting = function (x, y, w, h, obj) {

	let friend = false;
	const entities = engine.index.query(new engine.Entity(
		x,
		y,
		w,
		h)
	);

	for (let entity of entities) {
		if (entity.constructor.name == obj.name) {
			friend = entity;
			break;
		}
	}

	return friend;
};
*/