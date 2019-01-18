#include "Alien_Nest.h"

Alien_Nest::Alien_Nest() :
	m_position(800, 1500),
	m_velocity(0, 0),
	m_maxSpeed(1.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f)
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

	//create a new instance of missile
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
	//asign a new position to the nest
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
	//assign a random number between a and b 
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}



sf::Vector2f Alien_Nest::getPosition()
{
	//get position of sprite
	return m_sprite.getPosition();
}
sf::Vector2f Alien_Nest::getVelocity()
{
	//get the velocity of this object
	return m_velocity;
}


void Alien_Nest::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel)
{

	//update sprite to the objects position
	m_sprite.setPosition(m_position);
	//update sprite to face the right direction
	m_sprite.setRotation(m_orientation); 

	//keep the object bound to the map
	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);

	if (health<=0) {
		m_missile->die();
		timer++;
		if (timer % 10 == 0)
		{
			animate++;
		}
		//animate sprite when the ship is dead
		m_spriteExplosion.setTextureRect(sf::IntRect(310 * animate, 0, 320, 320));
		if (animate>15) {
			animate = 0;
			finishAnimate = true;
		}
	}
	if (health >0) {
		m_missile->update(cLevel);
		if (m_missile->getStatus() == true) {
			//if missile has been shot follow the player
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
					//std::cout << "Enemy spawned: " << i << std::endl;
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
	//set varibles when the ship is spawned
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
			//if the ship is dead draw explosion sprite
			window.draw(m_spriteExplosion);
			
		}
	
	}
	else {
		//else draw the ship and missile
		window.draw(m_sprite);
		m_missile->render(window);
	}
	
}
int Alien_Nest::getWidth()
{
	//get width
	return  128;
}
int Alien_Nest::getHeight()
{
	//get height
	return  256;
}

void Alien_Nest::hit(int damage)
{
	//this method assigns damage to the ships health
	//std::cout << health << std::endl;
	health = health - damage;
	m_explosion.x = m_position.x;
	m_explosion.y = m_position.y;
	m_spriteExplosion.setPosition(m_explosion);
}

int Alien_Nest::getHealth()
{
	//get the ships health
	return health;
}
int Alien_Nest::getId()
{
	//identification for the type of ship
	return 1;
}

bool Alien_Nest::radar(sf::Vector2f pos) {
	//get distance of the oncoming ship
	radarDistance = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));

	//oncoming ship within 750 fire missile
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
	//do nothing
	return 0;
}
bool Alien_Nest::checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive)
{
	//do nothing
	return 0;
}
int Alien_Nest::getScore()
{
	//do nothing
	return 0;
}
void Alien_Nest::setScore()
{
	//do nothing
}

int Alien_Nest::getDamageToPlayer()
{
	//how much damage has been inflicted to the player
	if (m_missile->getStatus())
	{
		return m_missile->damagedPlayer();
	}
	else
	{
		return 0;
	}
}