#include "Sweeper_Bot.h"

Sweeper_Bot::Sweeper_Bot() :
	m_position(800, 1000),
	m_velocity(0, 0),
	m_maxSpeed(1.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f)
{


	if (!m_texture.loadFromFile("assets/sweeper_bot/body_03.png")) {
		//error
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

	m_sprite.setOrigin(16, 32);

	if (!m_textureExplosion.loadFromFile("assets/explosion/explosion1.png"))
	{
		// error...
	}

	m_spriteExplosion.setTexture(m_textureExplosion);
	m_spriteExplosion.setOrigin(160, 160);

}


Sweeper_Bot::~Sweeper_Bot()
{

}

float Sweeper_Bot::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}

void Sweeper_Bot::setPos(sf::Vector2f newPos)
{
	//set positson to varible
	m_position = newPos;
}

void Sweeper_Bot::spawn(sf::Vector2f pos)
{
	//set sweeper bot varibles to set values
	m_position = pos;
	health = 50;
	timer = 0;
	animate = 0;
	finishAnimate = false;

	m_sprite.setPosition(m_position);
	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);

}


float Sweeper_Bot::getRandom(int a, int b)
{
	//get random number between two integers
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

sf::Vector2f Sweeper_Bot::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Sweeper_Bot::getVelocity()
{
	return m_velocity;
}


void Sweeper_Bot::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies, Level * cLevel)
{
	//in range of the player
	if (inRange ==false) {
		
		if (workerInRange) {
			kinematicSeek(playerPosition);
			//std::cout << "SEEK" << std::endl;
		}
		else {
			kinematicWander(target);
			//std::cout << "Wander" << std::endl;
		}
	}
	else {
		kinematicFlee(playerPosition);
		//std::cout << "FLEE" << std::endl;
	}

	
	if (m_timerCount >= m_timerCountLimit)
	{
		m_timerCount = 0;
		newTarget();
	}
	else
	{
		m_timerCount++;
	}

	//check for wall collison
	checkWall(cLevel);
	
	//fleeing from player and colliding with a wall
	//then stop 
	if (inRange == true && wall == true) {
		m_velocity.x = 0;
		m_velocity.y = 0;
	}

	//boundray
	if (m_sprite.getPosition().x > 5850)
	{
		m_position.x = 5850;
	}
	if (m_sprite.getPosition().x < 150)
	{
		m_position.x = 150;
	}
	if (m_sprite.getPosition().y < 150)
	{
		m_position.y = 150;
	}
	if (m_sprite.getPosition().y > 5850)
	{
		m_position.y = 150;
	}

	
	//only move when alive
	if (health > 0) {
		m_position = m_position + m_velocity;
	}

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);


	if (health <= 0) {
		timer++;
		if (timer % 10 == 0)
		{
			animate++;
		}
		//animate explosion sprite when dead
		m_spriteExplosion.setTextureRect(sf::IntRect(310 * animate, 0, 320, 320));
		if (animate>15) {
			animate = 0;
			finishAnimate = true;
		}
	}
}


void Sweeper_Bot::render(sf::RenderWindow & window)
{
	//draw explosion when dead
	if (health <= 0) {
		if (finishAnimate == false) {
			window.draw(m_spriteExplosion);
		}

	}
	else {
		//else draw ship 
		window.draw(m_sprite);
	}
}

int Sweeper_Bot::getWidth()
{
	//return width
	return  32; 
}
int Sweeper_Bot::getHeight()
{
	//return height
	return  64;
}

void Sweeper_Bot::hit(int damage)
{
	//assign damage via int variable to the ship
	//std::cout << "Sweeper bot hit" << std::endl;
	health = health - damage;
	m_explosion.x = m_position.x;
	m_explosion.y = m_position.y;
	m_spriteExplosion.setPosition(m_explosion);
}
int Sweeper_Bot::getHealth()
{
	//get health variable
	return health;
}

int Sweeper_Bot::getId()
{
	//return id value
	return 3;
}

int Sweeper_Bot::getScore()
{
	//get current score
	return score;
}
void Sweeper_Bot::setScore()
{
	//make score 0 when player takes score
	score = 0;
}

void Sweeper_Bot::kinematicSeek(sf::Vector2f pos)
{
	m_velocity = pos - m_position;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	//face the right direction
	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	m_orientation = m_orientation + 180;

}

void Sweeper_Bot::kinematicFlee(sf::Vector2f playerPosition)
{
	m_velocity = m_position - playerPosition;
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);
	//m_velocityF = m_velocityF * m_maxSpeed;
	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	m_velocity.x = m_velocity.x * m_maxSpeed;
	m_velocity.y = m_velocity.y * m_maxSpeed;

	//face the right direction
	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}

void Sweeper_Bot::kinematicWander(sf::Vector2f targetPosition)
{
	//pick a random direction and move towards it
	m_velocity = targetPosition - m_position;
	m_velocity = normalize(m_velocity);
	float orientation = getNewOrientation(m_sprite.getRotation(), length(m_velocity));
	orientation = orientation + m_maxRotation * ((rand() % 2) - 1);
	m_sprite.setRotation(orientation);
	m_velocity = sf::Vector2f(-sin(orientation), cos(orientation)) * m_maxSpeed;

}

bool Sweeper_Bot::radar(sf::Vector2f pos) {
	//get distance of oncoming object
	radarDistance = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));
	
	//check if object distance close to ship
	if (radarDistance < 200) {
		inRange = true;
		//std::cout << "in range " << std::endl;
	}
	else {
		//std::cout << "not in range " << std::endl;
		inRange = false;
	}

	return inRange;

}

bool Sweeper_Bot::workerRadar(sf::Vector2f pos) {
	//get distance of oncoming object
	workerRadarDis = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));

	//check if object distance close to ship
	if (workerRadarDis < 1000) {
		workerInRange = true;
		//std::cout << "in range " << std::endl;
		worker = pos;
	}
	else {
		//std::cout << "not in range " << std::endl;
		workerInRange = false;
	}

	return workerInRange;

}

bool Sweeper_Bot::checkWorkerCollision(sf::Vector2f pos, int width, int height, bool alive)
{
	//box collsion formula 
	if (alive == false) {
		if (m_sprite.getPosition().x < pos.x + width
			&& m_sprite.getPosition().x + 32> pos.x
			&&  m_sprite.getPosition().y + 64 > pos.y
			&&  m_sprite.getPosition().y < pos.y + height)
		{
			collison = true;
			score = score + 10;
			//std::cout << score << std::endl;
		}
		else {
			collison = false;
		}
	}


	return collison;
}

int Sweeper_Bot::getDamageToPlayer()
{
	//how much damage has been inflicted to the player
	return 0;
}

void Sweeper_Bot::newTarget()
{
	//get a new random target for wander
	target = sf::Vector2f(rand() % 6000, rand() % 6000);
}

void Sweeper_Bot::checkWall(Level * cLevel)
{
	// Get the square in front
	float posX = m_position.x + 32;
	float posY = m_position.y;

	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_position, m_sprite.getRotation());

	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);

	if (cLevel->collide(sf::Vector2i(x, y)))
	{
		newTarget();
		wall = true;
	}
	else {
		wall = false;
	}
}
sf::Vector2f Sweeper_Bot::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	//rotate ship to wander towards target
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}
float Sweeper_Bot::length(sf::Vector2f vel)
{
	//distance formula
	return (sqrt((vel.x * vel.x) + (vel.y * vel.y)));
}

sf::Vector2f Sweeper_Bot::normalize(sf::Vector2f vel)
{
	//how to normalize a vector
	if (length(vel) != 0)
		return sf::Vector2f(vel.x / length(vel), vel.y / length(vel));
	else
		return vel;
}