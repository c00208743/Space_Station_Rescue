#include "Game.h"

/// <summary>
/// @author JM
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

Game::Game()
	: m_window(sf::VideoMode(2000, 2000), "SFML Playground")

{
	m_window.setVerticalSyncEnabled(true);
	
	m_player = new Player();
	//m_worker = new Worker();


	for (int i = 0; i < 5; i++){
		Worker* m_worker = new Worker();
		workers.push_back(m_worker);
	}
	//hardcore start positions of worker bots
	workers[0]->setPosition(100, 200);
	workers[1]->setPosition(300, 200);
	workers[2]->setPosition(500, 200);
	workers[3]->setPosition(700, 200);
	workers[4]->setPosition(900, 200);

	Enemy* m_alienNest = new Alien_Nest();
	//Enemy* m_predatorShip = new Predator_Ship();
	//Enemy* m_sweeperBot = new Sweeper_Bot();
	
	enemies.push_back(m_alienNest);
	//enemies.push_back(m_predatorShip);
	//enemies.push_back(m_sweeperBot);
	
	//minimap + player camera
	m_follow.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	m_follow.setSize(sf::Vector2f(2000.f, 2000.f));

	

	// player 2 (right side of the screen)
	miniMap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
	miniMap.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));


}


/// <summary>
/// Main game entry point - runs untfil user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		
	}
}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;
	m_player->update(dt);
	
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->update(m_player->getPosition(), m_player);
		//worker collision
		if (m_player->checkWorkerCollision(workers[i]->getPosition(), 32, 64, workers[i]->getCollected())) {
			workers[i]->setCollected();
		}
		
	}
	

	//camera 
	m_follow.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	miniMap.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player, enemies);
		//check collision
		//wrapper this in gethealth 
		if (enemies[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(enemies[i]->getPosition(), enemies[i]->getWidth(), enemies[i]->getHeight()))
			{
				enemies[i]->hit(25);
			}
		}
		if (enemies[i]->getId() == 1)
		{
			enemies[i]->radar(m_player->getPosition());
		}
		
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(0, 0, 0));
	m_window.setView(miniMap);
	m_player->render(m_window);
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->render(m_window);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}
	

	m_window.setView(m_follow);
	m_player->render(m_window);
	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->render(m_window);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}
	m_window.display();
	


}

