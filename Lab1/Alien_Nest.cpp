#include "Alien_Nest.h"

Alien_Nest::Alien_Nest() :
	m_position(800, 1500),
	m_velocity(0, 0),
	m_maxSpeed(1.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	radius(200.0f),
	m_threshold(30.0f)
{


	if (!m_texture.loadFromFile("assets/alien_nest/body_01.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(64, 128);

	if (!m_textureExplosion.loadFromFile("assets/explosion/explosion1.png"))
	{
		// error...
	}

	m_spriteExplosion.setTexture(m_textureExplosion);
	m_spriteExplosion.setOrigin(160, 160);

	m_missile = new Missile();
}


Alien_Nest::~Alien_Nest()
{

}


float Alien_Nest::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Alien_Nest::setPos(sf::Vector2f newPos)
{
	m_position = newPos;
}

void Alien_Nest::boundary(float x, float y)
{
	if (x > 6100)
	{
		m_position.x = -100;
	}
	if (x < -100)
	{
		m_position.x = 6100;
	}
	if (y < -100)
	{
		m_position.y = 6100;
	}
	if (y > 6100)
	{
		m_position.y = -100;
	}

}

float Alien_Nest::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}



sf::Vector2f Alien_Nest::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Alien_Nest::getVelocity()
{
	return m_velocity;
}


void Alien_Nest::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel)
{


	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation); 

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);

	if (health<=0) {
		timer++;
		if (timer % 10 == 0)
		{
			animate++;
		}
		//animate++;
		m_spriteExplosion.setTextureRect(sf::IntRect(310 * animate, 0, 320, 320));
		if (animate>15) {
			animate = 0;
			finishAnimate = true;
		}
	}
	if (health >0) {
		m_missile->update(cLevel);
		if (m_missile->getStatus() == true) {
			m_missile->kinematicSeek(playerPosition);
		}

		// if Timer is above limit
		if (m_spawnCounter > m_spawnTimerLimit)
		{
			m_spawnCounter = 0;
			for (int i = 1; i < enemies.size(); i++)
			{
				// if dead
				if (enemies[i]->getHealth() <= 0)
				{
					std::cout << "Enemy spawned: " << i << std::endl;
					enemies[i]->spawn(m_position);
					break;
				}
			}

		}
		else
		{
			m_spawnCounter++;
		}
	}
	
}

void Alien_Nest::spawn(sf::Vector2f pos)
{
	m_position = pos;
	health = 50;
	timer = 0;
	animate = 0;
	finishAnimate = false;

	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

}

void Alien_Nest::render(sf::RenderWindow & window)
{
	
	if (health <= 0 ) {
		if (finishAnimate == false) {
			window.draw(m_spriteExplosion);
			
		}
	
	}
	else {
		window.draw(m_sprite);
		m_missile->render(window);
	}
	
}
int Alien_Nest::getWidth()
{
	return  128;
}
int Alien_Nest::getHeight()
{
	return  256;
}

void Alien_Nest::hit(int damage)
{
	//std::cout << health << std::endl;
	health = health - damage;
	m_explosion.x = m_position.x;
	m_explosion.y = m_position.y;
	m_spriteExplosion.setPosition(m_explosion);
}

int Alien_Nest::getHealth()
{
	return health;
}
int Alien_Nest::getId()
{
	return 1;
}

bool Alien_Nest::radar(sf::Vector2f pos) {
	radarDistance = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));

	if (radarDistance < 750 && !m_missile->getStatus()) {
		inRange = true;
		//std::cout << "in range " << std::endl;
		m_missile->fire(m_sprite.getPosition());
	}
	else {
		//std::cout << "not in range " << std::endl;
		inRange = false;
	}

	return inRange;

}

bool Alien_Nest::workerRadar(sf::Vector2f pos) {

	return 0;
}
bool Alien_Nest::checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive)
{
	//sweeper bot has no use for this method
	return 0;
}
int Alien_Nest::getScore()
{
	return 0;
}
void Alien_Nest::setScore()
{
	//do nothing
}

int Alien_Nest::getDamageToPlayer()
{
	//how much damage has been inflicted to the player
	return m_missile->damagedPlayer();
}