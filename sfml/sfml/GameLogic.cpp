#include "GameLogic.h"
#include <memory>

Entity *GameLogic::AddEntity (Entity *ent)
{
	if (ent->type == EntityType::Player) {
		assert (player2 == nullptr);
	if (player1 == nullptr)
		player1 = std::shared_ptr<Player> (static_cast<Player *> (ent));
	else
		player2 = std::shared_ptr<Player> (static_cast<Player *> (ent));
	}

	entities->push_back (ent);
	return ent;
}


void GameLogic::RemoveEntity (Entity *ent)
{
	entities->remove (ent);
}


void GameLogic::RemoveEntity (size_t id)
{
	entities->remove_if ([id](Entity *ent) {
		return ent->GetID () == id;
		});
}


bool GameLogic::IsPressed (int button)
{
	return inputs->contains (static_cast<sf::Keyboard::Key> (button));
}


void GameLogic::SetInputs (std::set<sf::Keyboard::Key> *inputsPointer)
{
	inputs = std::shared_ptr<std::set<sf::Keyboard::Key>> (inputsPointer);
}


void GameLogic::SetEntities (std::list<Entity *> *entitiesPointer)
{
	entities = entitiesPointer;
}


GameLogic::~GameLogic ()
{
	if(entities)
		for (auto& i : *entities)
			delete i;
}


void GameLogic::Update (float deltaTime)
{
	UpdateEntities (deltaTime);
}


void GameLogic::UpdatePlayer (Player *player, float deltaTime)
{
	const Attributes originalAttributes = player->attributes;
	for (auto it = player->buffs.begin (); it != player->buffs.end ();) {
		(*it)->apply (player->attributes);
		if ((*it)->Expired ()) {
			AttributeModifier *toRemove = *it;
			++it;
			player->buffs.remove (toRemove);
			delete toRemove;
		}
		else
			++it;
	}

	const static float grav = 21;
	const static float maxFallSpeed = 500;
	float& vsp = player->vsp;
	float& hsp = player->hsp;

	player->lastAttack -= deltaTime;
	if (IsPressed (player->controls.attack) && player->CanAttack ()) {
		AddEntity (new Bullet (player->GetCenter (), player->lastDir));
		player->lastAttack = 1.f / player->attributes.attackSpeed;
	}

	if (IsPressed (player->controls.powerMove) && player->buffs.empty ()) {
		AttributeModifier *newbuff = new DoubleSpeedBuff;
		player->buffs.push_back (newbuff);
	}

	short dir = (IsPressed (player->controls.moveDown) - IsPressed (player->controls.moveUp));
	vsp = dir * player->attributes.movSpeed;
	dir = (IsPressed (player->controls.moveRight) - IsPressed (player->controls.moveLeft));
	hsp = dir * player->attributes.movSpeed;

	if (dir == -1 || dir == 1)
		player->lastDir = dir;
	/*
	if (vsp < maxFallSpeed)
		vsp += grav;

	auto wallUnder = spacialIndex.CheckCollision (player->GetBoundingBox (0, deltaTime * vsp), EntityType::Wall);
	if (wallUnder) {

		//pixel perfect
		player->Move (0, wallUnder->GetTop () - player->GetTop () - 61);
		//while (!spacialIndex.CheckCollision (player->GetBoundingBox (0, 1), EntityType::Wall))
		//	player->Move (0, 1);
		//vsp = 0;
		//vsp = (IsPressed (player->controls.moveUp) ) * -player->attributes.jumpSpeed;
	}
	
		*/

	if (spacialIndex.CheckCollision (player->GetBoundingBox (deltaTime * hsp), EntityType::Wall)) {
		hsp = 0;
	}
	if (spacialIndex.CheckCollision (player->GetBoundingBox (0, deltaTime * vsp), EntityType::Wall)) {
		vsp = 0;
	}

	player->Move (deltaTime * hsp, deltaTime * vsp);


	if (hsp == 0 && vsp == 0)
		if (player->lastDir == -1)
			player->spriteHandler->SetSprite ("idle_l");
		else
			player->spriteHandler->SetSprite ("idle_r");

	else if (vsp != 0) {// todo ha nem találkozi ktalajjal
		if (player->lastDir == -1)
			player->spriteHandler->SetSprite ("jump_l");
		else
			player->spriteHandler->SetSprite ("jump_r");
	}
	else if (vsp == 0) {
		if (hsp > 0)
			player->spriteHandler->SetSprite ("run_r");
		else
			player->spriteHandler->SetSprite ("run_l");
	}

	player->attributes = originalAttributes;
}


void GameLogic::UpdateBullet (Bullet *bullet, float deltaTime)
{
	bullet->Move (deltaTime * bullet->direction * bullet->speed, 0);


	bool tooFar = (bullet->startPos.x - bullet->pos.x) *
		(bullet->startPos.x - bullet->pos.x) +
		(bullet->startPos.y - bullet->pos.y) *
		(bullet->startPos.y - bullet->pos.y) > 200000;
	Entity *hitWall = spacialIndex.CheckCollision (bullet->GetX (), bullet->GetY (), bullet->GetWidth (), bullet->GetHeight (), EntityType::Wall);


	if (tooFar || hitWall != nullptr) {
		entitiesToRemove.push_back (bullet);
		return;
	}

	Entity *hitEnemy = spacialIndex.CheckCollision (bullet->GetX (), bullet->GetY (), bullet->GetWidth (), bullet->GetHeight (), EntityType::Enemy);

	if (hitEnemy)
	{
		static_cast<Enemy *> (hitEnemy)->attributes.health -= 10;
		entitiesToRemove.push_back (bullet);
	}
}


void GameLogic::UpdateEnemy (Enemy *enemy, float deltaTime)
{
	if (Distance (player1->GetCenter ().x, player1->GetCenter ().y, enemy->GetCenter ().x, enemy->GetCenter ().y) < 200)
	{
		enemy->Move (Sign (player1->GetCenter ().x - enemy->GetCenter ().x), 0);
	}

	if (enemy->attributes.health <= 0)
		entitiesToRemove.push_back (enemy);
}


void GameLogic::UpdateEntity (Entity *e, float deltaTime)
{
	switch (e->type) {
	case EntityType::Player:
		UpdatePlayer (static_cast<Player *> (e), deltaTime);
		break;
	case EntityType::Bullet:
		UpdateBullet (static_cast<Bullet *> (e), deltaTime);
		break;
	case EntityType::Enemy:
		UpdateEnemy (static_cast<Enemy *> (e), deltaTime);
		break;

	default:
		break;
	}
}


void GameLogic::UpdateEntities (float deltaTime)
{
	for (auto it = entitiesToRemove.begin (); it != entitiesToRemove.end ();) {
		Entity *toDelete = *it;
		++it;
		entitiesToRemove.remove (toDelete);
		RemoveEntity (toDelete);
		delete toDelete;
	}
	spacialIndex.Clear ();
	spacialIndex.CreateIndex (entities);
	for (auto &e : *entities)
		UpdateEntity (e, deltaTime);
}