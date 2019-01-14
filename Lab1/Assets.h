#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <memory>
#include <iostream>


class assets {
public:
	~assets();
	static assets& instance();
	sf::Sprite* load_texture(std::string path, sf::RenderWindow* ren);
	assets();
	sf::Texture getTexture(int x);
private:
	std::map<std::string, sf::Sprite*> sprites;
	std::vector<sf::Texture> textures;
};
