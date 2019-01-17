#include "Level.h"

tile::tile()
{}

tile::tile(int x, int y, int tx, int ty, int w, int h, sf::Texture* t, bool c)
	: x(x), y(y), tx(tx), ty(ty), width(w), height(h), collide(c){

	sf::IntRect src = sf::IntRect(tx - 32, ty - 32, width, height);

	sf::IntRect dest = sf::IntRect(x, y, width, height);
	
	gridX = x / width;
	gridY = y / height;

	m_sprite.setTexture(*t);
	m_sprite.setTextureRect(src);
	m_sprite.setPosition(sf::Vector2f(x, y));
	m_checked = false;
	m_weight = INT_MAX;

}

void tile::draw(sf::RenderWindow* ren) {
	if (!ren)
		return;
	if (this != nullptr)
	{
		ren->draw(m_sprite);
	}
}

bool tile::getCollision()
{
	return collide;
}

void tile::setNeighbourWeights(std::shared_ptr<tile>(grid)[V][V])
{

	// Get x and y variable to make it handier
	m_neighbours = grid[gridX][gridY]->getNeighbours(grid, true);

	int lowestWeight = INT_MAX;
	//for each neighbour of this node (only straight line neighbours, not diagonals)
	for (int j = 0; j < m_neighbours.size(); j++) {
		std::shared_ptr<tile> n = m_neighbours[j];

		if (n->getWeight() < lowestWeight)
		{
			lowestWeight = n->getWeight();
		}
	}

	if (lowestWeight == INT_MAX)
	{
		m_checked = true;
		setWeight(0);
	}
	else
	{
		m_checked = true;
		setWeight(lowestWeight + 1);		
	}
}

std::vector<std::shared_ptr<tile>> tile::getNeighbours(std::shared_ptr<tile>(grid)[V][V], bool needWeights)
{
	std::vector<std::shared_ptr<tile>> ans;	// Put all neighbours in here
	
	bool checked;

	if (gridY > 2)
	{
		checked = grid[gridX][gridY - 1]->getChecked();
		if (!grid[gridX][gridY - 1]->getCollision() && (!checked || needWeights))
		{
			if (!needWeights)
			{
				grid[gridX][gridY - 1]->setChecked(true);
			}
			ans.push_back(grid[gridX][gridY - 1]);
		}
	}
	if (gridY < V - 3)
	{
		checked = grid[gridX][gridY + 1]->getChecked();
		if (!grid[gridX][gridY + 1]->getCollision() && (!grid[gridX][gridY + 1]->getChecked() || needWeights))
		{
			if (!needWeights)
			{
				grid[gridX][gridY + 1]->setChecked(true);
			}
			ans.push_back(grid[gridX][gridY + 1]);
		}
	}

	if (gridX > 2)
	{
		checked = grid[gridX - 1][gridY]->getChecked();
		if (!grid[gridX - 1][gridY]->getCollision() && (!grid[gridX - 1][gridY]->getChecked() || needWeights))
		{
			if (!needWeights)
			{
				grid[gridX - 1][gridY]->setChecked(true);
			}
			ans.push_back(grid[gridX - 1][gridY]);
		}
	}
	
	if (gridX < V - 3)
	{
		checked = grid[gridX + 1][gridY]->getChecked();
		if (!grid[gridX + 1][gridY]->getCollision() && (!grid[gridX + 1][gridY]->getChecked() || needWeights))
		{
			if (!needWeights)
			{
				grid[gridX + 1][gridY]->setChecked(true);
			}
			ans.push_back(grid[gridX + 1][gridY]);
		}
	}

	return ans;
}

int tile::getWeight()
{
	return m_weight;
}

void tile::setWeight(int w)
{
	m_weight = w;
}

bool tile::getChecked()
{
	return m_checked;
}

void tile::setChecked(bool c)
{
	m_checked = c;
}

void tile::reset()
{
	m_checked = false;
	m_weight = INT_MAX;
}

sf::Vector2i tile::getGridPos()
{
	return sf::Vector2i(gridX, gridY);
}

Level::Level(const std::string& name)
	: name(name), rows(0), cols(0) {
	
	tiles.resize(200);
	for (int i = 0; i < 200; ++i)
		tiles[i].resize(200);
}

void Level::load(const std::string& path, sf::RenderWindow* ren) {
	// Load and parse the Tiled map with tmxlite
	tmx::Map tiled_map;
	tiled_map.load(path);

	// We need to know the size of the map (in tiles)
	auto map_dimensions = tiled_map.getTileCount();
	rows = map_dimensions.y;
	cols = map_dimensions.x;

	// We also need to know the dimensions of the tiles.
	auto tilesize = tiled_map.getTileSize();
	tile_width = tilesize.x;
	tile_height = tilesize.y;

	// Load all of the tilesets and store them in a data structure.
	// I chose to store them in a map.
	auto& map_tilesets = tiled_map.getTilesets();
	assets * tempAssets;
	std::vector<sf::Sprite> spr;
	tempAssets = new assets();
	for (auto& tset : map_tilesets) {
		std::string imagePath = path.substr(0, path.find_last_of('/') + 1) + "Tilesets/";
		std::string test = tset.getImagePath();
		sf::Sprite tex = *tempAssets->load_texture(test, ren);
		spr.push_back(tex);
		tilesets.insert(std::pair<gid, sf::Sprite*>(tset.getFirstGID(), &spr[spr.size() - 1]));
	}


	tilesets[1]->setTexture(tempAssets->getTexture(1));
	texture = tempAssets->getTexture(1);
	bool collisionLayer = false;
	bool includeLayer = false;
	// iterate through each layer in the map,
	// poke each tile for the information you need, and store it in
	// our tiles data structure. 
	auto& map_layers = tiled_map.getLayers();
	for (auto& layer : map_layers) {
		// if this layer isn't a tile layer, we'll move on.
		if (layer->getType() != tmx::Layer::Type::Tile) {
			continue;
		}

		if (layer->getName() == "WallsTL") {
			collisionLayer = true;
			includeLayer = true;
		}
		else if (layer->getName() == "Background") {
			collisionLayer = false;
			includeLayer = true;
		}
		else
		{
			collisionLayer = false;
			includeLayer = false;
		}

		auto* tile_layer = dynamic_cast<const tmx::TileLayer*>(layer.get());

		// Grab all of this layer's tiles. 
		auto& layer_tiles = tile_layer->getTiles();

		for (auto y = 0; y < rows; ++y) {
			for (auto x = 0; x < cols; ++x) {
				auto tile_index = x + (y * cols);

				// Grab the GID of the tile we're at.
				auto cur_gid = layer_tiles[tile_index].ID;

				// If the GID is 0, that means it's an empty tile
				if (cur_gid == 0 || !includeLayer) {
					continue;
				}

				// Find the tileset that this tile belongs to. The tileset
				// whose first GID is less-than-or-equal to this GID, is
				// the tileset our GID belongs to. A tileset with a first
				// GID that is greater than this tile means that this tile
				// does not belong to that tileset.
				auto tset_gid = -1;
				for (auto& ts : tilesets) {
					if (ts.first <= cur_gid) {
						tset_gid = ts.first;
						break;
					}
				}

				// If we didn't find a valid tileset, skip the tile.
				if (tset_gid == -1) {
					continue;
				}

				// Normalize the GID.
				cur_gid -= tset_gid;

				// Find the dimensions of the tile sheet
				auto ts_width = 480;
				auto ts_height = 480;

				//SDL_QueryTexture(tilesets[tset_gid],
					//NULL, NULL, &ts_width, &ts_height);

				// Calculate the area on the tilesheet to draw from.
				auto region_x = (cur_gid % (ts_width / tile_width)) * tile_width;
				auto region_y = (cur_gid / (ts_width / tile_width)) * tile_height;

				// Calculate the world position of our tile
				auto x_pos = x * tile_width;
				auto y_pos = y * tile_height;
				
				
				
				//tile t(x_pos, y_pos,
				//	region_x, region_y, tile_width, tile_height, &texture, collisionLayer); // Add variable to say whether this should collide or not
				//tiles.push_back(t);
				
				grid[x][y] = std::make_unique<tile>(tile(x_pos, y_pos, region_x, region_y, tile_width, tile_height, &texture, collisionLayer));
			}
		}
	}
	giveWeights(grid, sf::Vector2i(9, 9));
}

void Level::draw(sf::RenderWindow* ren) {
	for (auto& layer : grid) {
		for (auto& tile : layer)
		{
			tile->draw(ren);
		}
	}
}

bool Level::collide(sf::Vector2i pos)
{
	return grid[pos.x][pos.y]->getCollision();
}

int Level::getWeight(sf::Vector2i gp)
{
	return grid[gp.x][gp.y]->getWeight();
}

void Level::path(std::shared_ptr<tile>(grid)[V][V], sf::Vector2i start, sf::Vector2i goal)
{
	std::vector<std::shared_ptr<tile>> path;
	std::shared_ptr<tile> lowestNeighbour;
	std::vector<std::shared_ptr<tile>> neighbours;
	path.push_back(grid[start.x][start.y]);


	neighbours = path[path.size() - 1]->getNeighbours(grid, true);

	lowestNeighbour = neighbours[0];

	while (lowestNeighbour->getWeight() != 0)
	{
		int lowestWeight = INT_MAX;

		neighbours = path[path.size() - 1]->getNeighbours(grid, true);
		lowestNeighbour = neighbours[0];

		for (int i = 0; i < neighbours.size(); i++)
		{
			if (neighbours[i]->getWeight() < path[path.size() - 1]->getWeight())
			{
				lowestNeighbour = neighbours[i];
			}
		}
		int currentWeight = path[path.size() - 1]->getWeight();
		int nextWeight = lowestNeighbour->getWeight();
		if (currentWeight == nextWeight)
		{
			break;
		}
		path.push_back(lowestNeighbour);
	}
}

void Level::reset(std::shared_ptr<tile>(grid)[V][V])
{
	for (int i = 3; i < V - 3; i++)
	{
		for (int j = 3; j < V - 3; j++)
		{
			grid[i][j]->reset();		
		}
	}

	//grid = emptyGrid;
}

void Level::updateWeights(sf::Vector2i p)
{
	reset(grid);
	giveWeights(grid, p);
}

void Level::giveWeights(std::shared_ptr<tile>(grid)[V][V], sf::Vector2i goal)
{
	std::vector<std::shared_ptr<tile>> queue;
	std::vector<std::shared_ptr<tile>> neighbours;
	queue.push_back(grid[goal.x][goal.y]);
	int checkRadius = 20;

	while (queue.size() > 0)
	{		
		queue[0]->setNeighbourWeights(grid);
		neighbours = grid[queue[0]->getGridPos().x][queue[0]->getGridPos().y]->getNeighbours(grid, false);
		for (int i = 0; i < neighbours.size(); i++)
		{
			
			if ((goal.x + checkRadius > neighbours[i]->getGridPos().x && goal.y + checkRadius > neighbours[i]->getGridPos().y) && (goal.x - checkRadius < neighbours[i]->getGridPos().x && goal.y - checkRadius < neighbours[i]->getGridPos().y))
			{
				if (neighbours[i]->getWeight() == INT_MAX)
				{
					queue.push_back(neighbours[i]);
				}
			}
		}
		queue.erase(queue.begin());
	}
}