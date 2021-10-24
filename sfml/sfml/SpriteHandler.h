#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <fstream>
#include <sstream>




class ResourceManager
{
public:
	static sf::Image* Get(std::string resourcePath)
	{
		static ResourceManager    instance;
		if (!instance.storage.contains(resourcePath)) {
			sf::Image image;
			image.loadFromFile(resourcePath);

			instance.storage.insert({resourcePath, image});
		}

		return instance.InnerGet(resourcePath);

	}
private:
	ResourceManager() {}
	std::map<std::string,  sf::Image> storage;
	sf::Image* InnerGet(std::string resourcePath) {
		return &storage.at(resourcePath);
	}
public:
	ResourceManager(ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
};



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
