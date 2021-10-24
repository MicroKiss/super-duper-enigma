#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <sstream>

#include "ResourceManager.h"


class SpriteSheet
{
public:
	SpriteSheet (const char* filePath,
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
	void Draw (std::shared_ptr<sf::RenderWindow>window);
	void Update (float deltaTime);
	void SetSprite (std::string name);
	std::string GetSpriteName () const;
	void LoadSpriteSheet (std::string name,
						  char const* const filePath,
						  unsigned short width,
						  unsigned short height,
						  unsigned short numberOfSprites = 1,
						  float updateInterval = 0.1,
						  bool loop = true);

	sf::Sprite currentSprite;
	unsigned short currentSpriteIndex = 0;
	SpriteSheet* currentSpriteSheet = nullptr;
	std::string currentSpriteSheetName;
	SpriteHandler () {};
	std::map<std::string, SpriteSheet> loadedSpriteSheets;
	float timeSinceLastUpdate = 0;
};