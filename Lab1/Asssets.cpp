#include "Assets.h"

assets::assets() {}

assets::~assets() {
	for (auto sprite : sprites) {
		if (sprite.second) {
			sprite.second = nullptr;
		}
	}
}

assets& assets::instance() {
	static std::unique_ptr<assets> inst(new assets());
	return *inst;
}

// SDL_Texture == sf::Texture
// sdl_surface == sf::sprite
// SDL_Renderer == sf::renderwindow


sf::Texture assets::getTexture(int x)
{
	return textures[x];
}


sf::Sprite* assets::load_texture(std::string path, sf::RenderWindow* ren) {
	auto already_loaded = sprites.find(path);
	if (already_loaded != sprites.end()) {
		return already_loaded->second;
	}

	//auto surf = IMG_Load(path.c_str());
	sf::Texture * tex = &sf::Texture();// = &sf::Texture();
	textures.push_back(sf::Texture());
	int numOfTexs = textures.size();
	if (!textures[numOfTexs - 1].loadFromFile(path.c_str())) {
		std::cerr << "ERROR: failed to load " << path << "\n";
		return nullptr;
	}

	//auto tex = SDL_CreateTextureFromSurface(ren, surf);
	
	sf::Sprite * sprite = &sf::Sprite();
	sprite->setTexture(textures[numOfTexs - 1]);
	/*if (!sprite)  {
		std::cerr << "ERROR: failed to create texture: "
			<< SDL_GetError() << "\n";
	}*/

	sprites.insert(std::pair<std::string, sf::Sprite*>(path, sprite));

	return sprite;
}
