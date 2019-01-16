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
	Level* m_level;
	std::string const path = "assets/maps/Practice.tmx";
	
	//std::vector<Enemy*> enemies;

};


