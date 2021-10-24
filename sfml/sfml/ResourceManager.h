#pragma once

/*
So images will only load once 
*/
class ResourceManager
{
public:
	static sf::Image* Get (std::string resourcePath)
	{
		static ResourceManager    instance;
		if (!instance.storage.contains (resourcePath)) {
			sf::Image image;
			image.loadFromFile (resourcePath);

			instance.storage.insert ({resourcePath, image});
		}

		return instance.InnerGet (resourcePath);

	}
private:
	ResourceManager () {}
	std::map<std::string, sf::Image> storage;
	sf::Image* InnerGet (std::string resourcePath)
	{
		return &storage.at (resourcePath);
	}
public:
	ResourceManager (ResourceManager const&) = delete;
	void operator=(ResourceManager const&) = delete;
};
