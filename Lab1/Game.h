#pragma once
#include "Player.h"
#include "Worker.h"
#include "Enemy.h"
#include "Alien_Nest.h"
#include "Predator_Ship.h"
#include "Sweeper_Bot.h"
#include "Level.h"


#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();

	void run();

private:

	void update(double dt);
	void render();
	void processEvents();

	sf::RenderWindow m_window; // main SFML window
	sf::View miniMap;
	sf::View m_follow;
	Player* m_player;
	//Worker* m_worker;
	std::vector<Worker*> workers;
	std::vector<Enemy*> enemies;
	std::vector<Enemy*> nest;
	std::vector<Enemy*> nest2;
	std::vector<Enemy*> nest3;
	std::vector<Enemy*> nest4;
	Level* m_level;
	std::string const path = "assets/maps/Practice.tmx";
	
	int m_workersCollected;
	sf::Texture m_winTexture;
	sf::Sprite m_winSprite;
	//std::vector<Enemy*> enemies;
	sf::RectangleShape m_radar;
};


