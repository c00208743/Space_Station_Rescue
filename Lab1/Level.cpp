#include "Level.h"

tile::tile(int x, int y, int tx, int ty, int w, int h, sf::Texture* t)
	: x(x), y(y), tx(tx), ty(ty), width(w), height(h) {

	sf::IntRect src = sf::IntRect(tx - 32, ty - 32, width, height);

	sf::IntRect dest = sf::IntRect(x, y, width, height);
	

	m_sprite.setTexture(*t);
	m_sprite.setTextureRect(src);
	m_sprite.setPosition(sf::Vector2f(x, y));

}

void tile::draw(sf::RenderWindow* ren) {
	if (!ren)
		return;

	ren->draw(m_sprite);

	//SDL_RenderCopy(ren, sheet, &src, &dest);
}

Level::Level(const std::string& name)
	: name(name), rows(0), cols(0) {

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
			// Put a variable to say "This is the layer to collide with"
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
				if (cur_gid == 0) {
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
				tile t(x_pos, y_pos,
					region_x, region_y, tile_width, tile_height, &texture); // Add variable to say whether this should collide or not
				tiles.push_back(t);
			}
		}
	}
}

void Level::draw(sf::RenderWindow* ren) {
	for (auto& tile : tiles) {
		tile.draw(ren);
	}
}