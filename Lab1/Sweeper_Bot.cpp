#include "Sweeper_Bot.h"

Sweeper_Bot::Sweeper_Bot() :
	m_position(800, 1000),
	m_velocity(0, 0),
	m_maxSpeed(1.5f),
	m_maxRotation(20.0f),
	m_timeToTarget(100.0f),
	radius(200.0f),
	m_threshold(30.0f)
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
	m_position = newPos;
}

void Sweeper_Bot::spawn(sf::Vector2f pos)
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

void Sweeper_Bot::boundary(float x, float y)
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

float Sweeper_Bot::getRandom(int a, int b)
{
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
	//player
	if (inRange ==false) {
		
		if (workerInRange) {
			kinematicSeek(worker);
			//std::cout << "SEEK" << std::endl;
		}
		else {
			kinematicWander(playerPosition);
			//std::cout << "Wander" << std::endl;
		}
	}
	else {
		kinematicFlee(playerPosition);
		//std::cout << "FLEE" << std::endl;
	}

	

	if (health > 0) {
		m_position = m_position + m_velocity;
	}

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);

	if (health <= 0) {
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
}


void Sweeper_Bot::render(sf::RenderWindow & window)
{
	if (health <= 0) {
		if (finishAnimate == false) {
			window.draw(m_spriteExplosion);
		}

	}
	else {
		window.draw(m_sprite);
	}
}

int Sweeper_Bot::getWidth()
{
	return  32; 
}
int Sweeper_Bot::getHeight()
{
	return  64;
}

void Sweeper_Bot::hit(int damage)
{
	//std::cout << "Sweeper bot hit" << std::endl;
	health = health - damage;
	m_explosion.x = m_position.x;
	m_explosion.y = m_position.y;
	m_spriteExplosion.setPosition(m_explosion);
}
int Sweeper_Bot::getHealth()
{
	return health;
}

int Sweeper_Bot::getId()
{
	return 3;
}

int Sweeper_Bot::getScore()
{
	return score;
}
void Sweeper_Bot::setScore()
{
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

	m_orientation = getNewOrientation(m_orientation, m_velocityF);

}

void Sweeper_Bot::kinematicWander(sf::Vector2f playerPosition)
{
	//steering = new SteeringOutput()
	//steering = velocity

	wanderOrientation += getRandom(-1, +1) * wanderRate;


	targetOrientation = wanderOrientation + m_orientation;
	//sf::Vector2f wanderOffset(25.f, 25.f);
	float wanderOffset(25.f);
	float wanderRadius(250.f);
	orientationAsVector = asVector(m_orientation);
	target = m_position + wanderOffset * orientationAsVector;
	targetOrientationAsVector = asVector(targetOrientation);
	target += wanderRadius * targetOrientationAsVector;
	//face(target)
	m_velocity = target - m_position;

	//Get magnitude of vector#
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y*m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	//get new orientation
	m_orientation = getNewOrientation(m_orientation, m_velocityF);
	//steering.linear = maxAcc * my.orientation.asVector()
	orientationAsVector = asVector(m_orientation);
	m_velocity = m_maxSpeed * orientationAsVector;

	//return steering

}

bool Sweeper_Bot::radar(sf::Vector2f pos) {
	radarDistance = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));
	

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
	workerRadarDis = sqrt((pos.x - m_sprite.getPosition().x)*(pos.x - m_sprite.getPosition().x)
		+ (pos.y - m_sprite.getPosition().y)*(pos.y - m_sprite.getPosition().y));


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

sf::Vector2f Sweeper_Bot::asVector(float orientation)
{
	return sf::Vector2f(sinf(orientation), cosf(orientation));

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