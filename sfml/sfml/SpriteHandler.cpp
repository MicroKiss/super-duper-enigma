#include "SpriteHandler.h"
#include <iostream>


SpriteSheet::SpriteSheet (
	const char *filePath,
	unsigned short width,
	unsigned short height,
	unsigned short numberOfSprites,
	float updateInterval,
	bool loop
)
{
	if (numberOfSprites == 1)
		singleSprite = true;
	this->height = height;
	this->width = width;
	this->numberOfSprites = numberOfSprites;
	this->updateInterval = updateInterval;
	this->loop = loop;
	if (!texture.loadFromImage (*ResourceManager::Get (filePath)))
		throw 1;
}


void SpriteHandler::Draw (sf::RenderWindow *const window)
{
	window->draw (currentSprite);
}

void SpriteHandler::Update (float deltaTime)
{
	if (currentSpriteSheet->singleSprite)
		return;
	if (!currentSpriteSheet->loop && currentSpriteSheet->numberOfSprites - 1 == currentSpriteIndex)
		return;

	timeSinceLastUpdate += deltaTime;

	if (timeSinceLastUpdate > currentSpriteSheet->updateInterval)
	{
		timeSinceLastUpdate = 0;
		currentSpriteIndex = (currentSpriteIndex + 1) % currentSpriteSheet->numberOfSprites;
		currentSprite.setTextureRect (sf::IntRect (currentSpriteIndex * currentSpriteSheet->width, 0, currentSpriteSheet->width, currentSpriteSheet->height));
	}
}

void SpriteHandler::SetSprite (std::string name)
{
	if (loadedSpriteSheets.count (name) == 0)
		throw "not existing name";
	if (&loadedSpriteSheets.at (name) == currentSpriteSheet)
		return;
	int a = 2;
	currentSpriteSheet = &loadedSpriteSheets.at (name);
	currentSprite.setTexture (currentSpriteSheet->texture);
	currentSprite.setTextureRect (sf::IntRect (0, 0, currentSpriteSheet->width, currentSpriteSheet->height));
	currentSpriteIndex = 0;
	currentSpriteSheetName = name;
}

std::string SpriteHandler::GetSpriteName () const
{
	return currentSpriteSheetName;
}

void SpriteHandler::LoadSpriteSheet (
	std::string name,
	char const *const filePath,
	unsigned short width,
	unsigned short height,
	unsigned short numberOfSprites,
	float updateInterval,
	bool loop)
{
	SpriteSheet spriteSheet (filePath, width, height, numberOfSprites, updateInterval, loop);
	loadedSpriteSheets.emplace (name, spriteSheet);

	if (currentSpriteSheet == nullptr)
		SetSprite (name);

}

