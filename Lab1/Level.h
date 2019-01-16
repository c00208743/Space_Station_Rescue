#pragma once

#include <iostream>
#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/TileLayer.hpp>
#include <map>
#include "Assets.h"

#define V 200

enum Direction
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

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
	int gridX;
	int gridY;

	bool collide;

	tile();
	tile(int x, int y, int tx, int ty, int w, int h, sf::Texture* t, bool c);
	void draw(sf::RenderWindow* ren);
	bool getCollision();

	//Path finding
	int getWeight();
	void setWeight(int w); 
	bool getChecked();
	void setChecked(bool c);
	void reset();
	sf::Vector2i getGridPos();
	std::vector<std::shared_ptr<tile>> getNeighbours(std::shared_ptr<tile>(grid)[V][V], bool needWeights);
	void setNeighbourWeights(std::shared_ptr<tile>(grid)[V][V]);
	
	// Path finding variables
	std::vector<std::shared_ptr<tile>> m_neighbours;
	bool m_checked;
	std::map<Direction, bool> m_neighbourVisited;
	int m_weight;

};

class Level
{
public:
	Level(const std::string& name);
	void load(const std::string& path, sf::RenderWindow* ren);
	void draw(sf::RenderWindow* ren);
	void updateWeights(sf::Vector2i p);
	bool collide(sf::Vector2i pos);
	int getWeight(sf::Vector2i gp);

private:
	std::string name;

	int rows;
	int cols;

	int tile_width;
	int tile_height;

	sf::Texture texture;

	std::vector<std::vector<tile>> tiles;
	std::shared_ptr<tile> grid[V][V];

	std::map<gid, sf::Sprite*> tilesets;
	


	// Path finding 
	void path(std::shared_ptr<tile>(grid)[V][V], sf::Vector2i start, sf::Vector2i goal);
	void reset(std::shared_ptr<tile>(grid)[V][V]);
	void giveWeights(std::shared_ptr<tile>(grid)[V][V], sf::Vector2i goal);
};