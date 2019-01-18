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


	for (int i = 0; i < 10; i++){
		Worker* m_worker = new Worker();
		workers.push_back(m_worker);
	}

	//hardcode start positions of worker bots
	workers[0]->setPosition(1050, 425);
	workers[1]->setPosition(1100, 1750);
	workers[2]->setPosition(1400, 2950);
	workers[3]->setPosition(450, 3750);
	workers[4]->setPosition(1400, 5325);
	workers[5]->setPosition(3650, 3725);
	workers[6]->setPosition(2825, 2950);
	workers[7]->setPosition(5850, 5200);
	workers[8]->setPosition(5725, 3200);
	workers[9]->setPosition(4875, 1400);

	Enemy* m_alienNest = new Alien_Nest();
	Enemy* m_predatorShip = new Predator_Ship();
	Enemy* m_sweeperBot = new Sweeper_Bot();


	Enemy* m_alienNestRoom2 = new Alien_Nest();
	m_alienNestRoom2->setPos(sf::Vector2f(1728, 384));
	Enemy* m_ANR2P1 = new Predator_Ship();
	Enemy* m_ANR2P2 = new Predator_Ship();
	Enemy* m_ANR2P3 = new Predator_Ship();
	Enemy* m_ANR2P4 = new Predator_Ship();
	Enemy* m_ANR2P5 = new Predator_Ship();

	Enemy* m_alienNestRoom3 = new Alien_Nest();
	m_alienNestRoom3->setPos(sf::Vector2f(3225, 5425));
	Enemy* m_ANR3P1 = new Predator_Ship();
	Enemy* m_ANR3P2 = new Predator_Ship();
	Enemy* m_ANR3P3 = new Predator_Ship();
	Enemy* m_ANR3P4 = new Predator_Ship();
	Enemy* m_ANR3P5 = new Predator_Ship();

	Enemy* m_alienNestRoom4 = new Alien_Nest();
	m_alienNestRoom4->setPos(sf::Vector2f(3225, 3325));
	Enemy* m_ANR4P1 = new Predator_Ship();
	Enemy* m_ANR4P2 = new Predator_Ship();
	Enemy* m_ANR4P3 = new Predator_Ship();
	Enemy* m_ANR4P4 = new Predator_Ship();
	Enemy* m_ANR4P5 = new Predator_Ship();

	Enemy* m_alienNestRoom5 = new Alien_Nest();
	m_alienNestRoom5->setPos(sf::Vector2f(4925, 1100));
	Enemy* m_ANR5P1 = new Predator_Ship();
	Enemy* m_ANR5P2 = new Predator_Ship();
	Enemy* m_ANR5P3 = new Predator_Ship();
	Enemy* m_ANR5P4 = new Predator_Ship();
	Enemy* m_ANR5P5 = new Predator_Ship();


	for (int i = 0; i < 5; i++) {
		Enemy* m_sweeperBot = new Sweeper_Bot();
		enemies.push_back(m_sweeperBot);
	}
	//set positions of the sweepers
	enemies[0]->setPos(sf::Vector2f(1025, 1050));
	enemies[1]->setPos(sf::Vector2f(2100, 4125));
	enemies[2]->setPos(sf::Vector2f(4300, 5750));
	enemies[3]->setPos(sf::Vector2f(4400, 4275));
	enemies[4]->setPos(sf::Vector2f(3125, 1500));

	//add alien nests and preds to nest vector
	nest.push_back(m_alienNestRoom2);
	nest.push_back(m_ANR2P1);
	nest.push_back(m_ANR2P2);
	nest.push_back(m_ANR2P3);
	nest.push_back(m_ANR2P4);
	nest.push_back(m_ANR2P5);

	nest2.push_back(m_alienNestRoom3);
	nest2.push_back(m_ANR3P1);
	nest2.push_back(m_ANR3P2);
	nest2.push_back(m_ANR3P3);
	nest2.push_back(m_ANR3P4);
	nest2.push_back(m_ANR3P5);

	nest3.push_back(m_alienNestRoom4);
	nest3.push_back(m_ANR4P1);
	nest3.push_back(m_ANR4P2);
	nest3.push_back(m_ANR4P3);
	nest3.push_back(m_ANR4P4);
	nest3.push_back(m_ANR4P5);

	nest4.push_back(m_alienNestRoom5);
	nest4.push_back(m_ANR5P1);
	nest4.push_back(m_ANR5P2);
	nest4.push_back(m_ANR5P3);
	nest4.push_back(m_ANR5P4);
	nest4.push_back(m_ANR5P5);

	m_level = new Level("Main Level");
	m_level->load(path, &m_window);
	
	//minimap + player camera
	m_follow.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	m_follow.setSize(sf::Vector2f(2000.f, 2000.f));

	// player 2 (right side of the screen)
	miniMap.setViewport(sf::FloatRect(0.75f, 0.f, 0.25f, 0.25f));
	miniMap.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));

	//radar background
	m_radar.setSize(sf::Vector2f(500, 500));
	m_radar.setFillColor(sf::Color::Black);
	
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

	m_radar.setPosition(m_player->getPosition().x + 500, m_player->getPosition().y -750);

	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->update(m_level);
		//worker collision with the player
		if (m_player->checkWorkerCollision(workers[i]->getPosition(), 32, 64, workers[i]->getCollected())) {
			workers[i]->setCollected();
		}
		
		
	}
	
	m_player->update(dt, m_level);

	//camera 
	m_follow.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	miniMap.setCenter(sf::Vector2f(m_player->getPosition().x, m_player->getPosition().y));
	
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->update(m_player->getPosition(), m_player, enemies, m_level);
		//if enemy is alive check for bullet collison
		if (enemies[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(enemies[i]->getPosition(), enemies[i]->getWidth(), enemies[i]->getHeight()) == true)
			{
				//if collide with bullet assign damage
 				enemies[i]->hit(25);
			}
		}
		//id 1 = alien nest
		//id 2 = predator
		if (enemies[i]->getId() == 1 || enemies[i]->getId() == 2)
		{
			enemies[i]->radar(m_player->getPosition());
			//set player health
			m_player->setHealth(enemies[i]->getDamageToPlayer());
		}

		
		//id 3 = sweeper 
		if (enemies[i]->getId() == 3)
		{
			enemies[i]->radar(m_player->getPosition());
			//if sweeper is alive 
			if (enemies[i]->getHealth() <= 0) {
				//give score to player
				m_player->setScore(enemies[i]->getScore());
				enemies[i]->setScore();
			}
			for (int j = 0; j < workers.size(); j++)
			{
				//if dead dont seek worker
				if (workers[j]->getCollected() == false) {
					enemies[i]->workerRadar(workers[j]->getPosition());
				}
				
				if (enemies[i]->checkWorkerCollision(workers[j]->getPosition(), 32, 64, workers[j]->getCollected())) {
					workers[j]->setCollected();
				}
			}
			
		}
		
	}

	for (int i = 0; i < nest.size(); i++)
	{
		
		nest[i]->update(m_player->getPosition(), m_player, nest, m_level);
		//wrapper this in gethealth 
		if (nest[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(nest[i]->getPosition(), nest[i]->getWidth(), nest[i]->getHeight()) == true)
			{
 				nest[i]->hit(25);
			}
		}
		if (nest[i]->getId() == 1 || nest[i]->getId() == 2)
		{
			nest[i]->radar(m_player->getPosition());
			//set player health
			m_player->setHealth(nest[i]->getDamageToPlayer());
		}
	}

	for (int i = 0; i < nest2.size(); i++)
	{

		nest2[i]->update(m_player->getPosition(), m_player, nest2, m_level);
		//wrapper this in gethealth 
		if (nest2[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(nest2[i]->getPosition(), nest2[i]->getWidth(), nest2[i]->getHeight()) == true)
			{
				nest2[i]->hit(25);
			}
		}
		if (nest2[i]->getId() == 1 || nest2[i]->getId() == 2)
		{
			nest2[i]->radar(m_player->getPosition());
			//set player health
			m_player->setHealth(nest2[i]->getDamageToPlayer());
		}
	}

	for (int i = 0; i < nest3.size(); i++)
	{

		nest3[i]->update(m_player->getPosition(), m_player, nest3, m_level);
		//wrapper this in gethealth 
		if (nest3[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(nest3[i]->getPosition(), nest3[i]->getWidth(), nest3[i]->getHeight()) == true)
			{
				nest3[i]->hit(25);
			}
		}
		if (nest3[i]->getId() == 1 || nest3[i]->getId() == 2)
		{
			nest3[i]->radar(m_player->getPosition());
			//set player health
			m_player->setHealth(nest3[i]->getDamageToPlayer());
		}
	}

	for (int i = 0; i < nest4.size(); i++)
	{

		nest4[i]->update(m_player->getPosition(), m_player, nest4, m_level);
		//wrapper this in gethealth 
		if (nest4[i]->getHealth() > 0) {
			if (m_player->checkBulletCollision(nest4[i]->getPosition(), nest4[i]->getWidth(), nest4[i]->getHeight()) == true)
			{
				nest4[i]->hit(25);
			}
		}
		if (nest4[i]->getId() == 1 || nest4[i]->getId() == 2)
		{
			nest4[i]->radar(m_player->getPosition());
			//set player health
			m_player->setHealth(nest4[i]->getDamageToPlayer());
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
	//render player camera
	m_window.setView(m_follow);
	m_level->draw(&m_window);
	
	m_player->render(m_window);

	for (int i = 0; i < workers.size(); i++)
	{
		workers[i]->render(m_window);
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->render(m_window);
	}
	for (int i = 0; i < nest.size(); i++)
	{
		nest[i]->render(m_window);
	}
	for (int i = 0; i < nest2.size(); i++)
	{
		nest2[i]->render(m_window);
	}


	for (int i = 0; i < nest3.size(); i++)
	{
		nest3[i]->render(m_window);
	}


	for (int i = 0; i < nest4.size(); i++)
	{
		nest4[i]->render(m_window);
	}

	//render minimap
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

	for (int i = 0; i < nest.size(); i++)
	{
		nest[i]->render(m_window);
	}

	for (int i = 0; i < nest2.size(); i++)
	{
		nest2[i]->render(m_window);
	}

	for (int i = 0; i < nest3.size(); i++)
	{
		nest3[i]->render(m_window);
	}
	
	for (int i = 0; i < nest4.size(); i++)
	{
		nest4[i]->render(m_window);
	}
	m_window.display();
}
