#pragma once

#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <map>
#include "Assets.h"


typedef int gid;

// Stores information about an individual tile to be
// displayed.
struct tile {
	sf::Sprite m_sprite;
	// x coordinate in the world
	int x;
	// y coordinate in the world
	int y;
	// the x coordinate on the sprite sheet
	int tx;
	// the y coordinate on the sprite sheet
	int ty;
	int width;
	int height;

	tile(int x, int y, int tx, int ty, int w, int h, sf::Texture* t);
	void draw(sf::RenderWindow* ren);
};

class Level
{
public:
	Level(const std::string& name);
	void load(const std::string& path, sf::RenderWindow* ren);
	void draw(sf::RenderWindow* ren);

private:
	std::string name;

	int rows;
	int cols;

	int tile_width;
	int tile_height;

	sf::Texture texture;

	std::vector<tile> tiles;

	std::map<gid, sf::Sprite*> tilesets;
};