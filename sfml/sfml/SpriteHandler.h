#pragma once
#include <SFML/Graphics.hpp>
#include <map>


class SpriteSheet
{
public:
	SpriteSheet (const char *filePath,
		unsigned short width,
		unsigned short height,
		unsigned short numberOfSprites = 1,
		float updateInterval = 0.1,
		bool loop = true
	);

public:
	unsigned short  width;
	unsigned short  height;
	unsigned short numberOfSprites;
	sf::Texture texture;
	float updateInterval;
	bool singleSprite = false;
	bool loop;
};


class SpriteHandler
{
public:
	void Draw (sf::RenderWindow *const window);
	void Update (float deltaTime);
	void SetSprite (std::string name);
	std::string GetSpriteName () const;
	void LoadSpriteSheet (std::string name,
		char const *const filePath,
		unsigned short width,
		unsigned short height,
		unsigned short numberOfSprites = 1,
		float updateInterval = 0.1,
		bool loop = true);

public:
	sf::Sprite currentSprite;
	unsigned short currentSpriteIndex = 0;
	SpriteSheet *currentSpriteSheet = nullptr;
	std::string currentSpriteSheetName;
	SpriteHandler () {};
	std::map<std::string, SpriteSheet> loadedSpriteSheets;
	float timeSinceLastUpdate = 0;
};



class SingletonBulletSpriteHandler
{
	SpriteHandler *spriteHandler = nullptr;

	// Private constructor so that no objects can be created.
	SingletonBulletSpriteHandler () {
		spriteHandler = new SpriteHandler;
		spriteHandler->LoadSpriteSheet ("idle", "assets/bullet.png", 10, 10, 1);
		spriteHandler->SetSprite ("idle");
	}

	~SingletonBulletSpriteHandler () {
		delete spriteHandler;
	}

	SpriteHandler *getData () {
		return this->spriteHandler;
	}
public:
	static SingletonBulletSpriteHandler *getInstance () {
		static SingletonBulletSpriteHandler *instance = new SingletonBulletSpriteHandler;
		return instance;
	}
	static SpriteHandler *GetSpriteHandler () {
		return getInstance ()->getData ();
	}
};


class SingletonWallSpriteHandler
{
	SpriteHandler *spriteHandler = nullptr;

	// Private constructor so that no objects can be created.
	SingletonWallSpriteHandler () {
		spriteHandler = new SpriteHandler;
		spriteHandler->LoadSpriteSheet ("idle", "assets/wall.png", 64, 64, 1);
		spriteHandler->SetSprite ("idle");
	}

	~SingletonWallSpriteHandler () {
		delete spriteHandler;
	}

	SpriteHandler *getData () {
		return this->spriteHandler;
	}
public:
	static SingletonWallSpriteHandler *getInstance () {
		static SingletonWallSpriteHandler *instance = new SingletonWallSpriteHandler;
		return instance;
	}
	static SpriteHandler *GetSpriteHandler () {
		return getInstance ()->getData ();
	}
};

class SingletonEnemySpriteHandler
{
	SpriteHandler *spriteHandler = nullptr;

	// Private constructor so that no objects can be created.
	SingletonEnemySpriteHandler () {
		spriteHandler = new SpriteHandler;
		spriteHandler->LoadSpriteSheet ("idle", "assets/enemy.png", 48, 64, 1);
		spriteHandler->SetSprite ("idle");
	}

	~SingletonEnemySpriteHandler () {
		delete spriteHandler;
	}

	SpriteHandler *getData () {
		return this->spriteHandler;
	}
public:
	static SingletonEnemySpriteHandler *getInstance () {
		static SingletonEnemySpriteHandler *instance = new SingletonEnemySpriteHandler;
		return instance;
	}
	static SpriteHandler *GetSpriteHandler () {
		return getInstance ()->getData ();
	}
};