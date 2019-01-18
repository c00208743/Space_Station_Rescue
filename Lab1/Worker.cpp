#include "Worker.h"
#include "math.h"


#define M_PI   3.14159265358979323846264338327950288

Worker::Worker() :
	m_position(800, 800),
	m_velocity(0, 0),
	m_maxSpeed(0.5f)
{

	
	if (!m_texture.loadFromFile("assets/worker_bot/body_02.png"))
	{
		// error...
	}

	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(m_position);

	m_velocity.x = getRandom(20, -10);
	m_velocity.y = getRandom(20, -10);
	m_sprite.setOrigin(16, 32);
	/* initialize random seed: */
	srand(time(NULL));

	newTarget();

	m_timerCount = 0;
}


Worker::~Worker()
{
}

void Worker::newTarget()
{
	//create a vector with randomized vaules
	target = sf::Vector2f(rand() % 6000, rand() % 6000);
}

sf::Vector2f Worker::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	//rotate is use to let the ship face the right direction
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}

void Worker::update(Level * cLevel)
{
	//only update if a worker is collected
	if (collected == false) {
		if (m_timerCount >= m_timerCountLimit)
		{
			m_timerCount = 0;
			newTarget();
		}
		else
		{
			m_timerCount++;
		}

		kinematicWander(target);
		m_position = m_position + m_velocity;
		m_sprite.setPosition(m_position);
		checkWall(cLevel);
	}
	
}


void Worker::checkWall(Level * cLevel)
{
	// Get the square in front
	float posX = m_position.x + 64;
	float posY = m_position.y;
	
	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_sprite.getPosition(), m_sprite.getRotation());

	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);

	if (cLevel->collide(sf::Vector2i(x, y)))
	{
		m_velocity = sf::Vector2f(0, 0);
		target.x = -target.x;
		target.y = -target.y;
		//newTarget();
	}
}

float Worker::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / M_PI);
	}
	else {
		
		return currentOrientation;
	}

}

float Worker::getRandom(int a, int b)
{
	//get random number between two choosen values
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

sf::Vector2f Worker::getPosition()
{
	//get position of ship
	return m_sprite.getPosition();
}
void Worker::setPosition(float x, float y)
{
	//set position using two variables
	m_position.x = x;
	m_position.y = y;
}

sf::Vector2f Worker::getVelocity()
{
	//get current velocity
	return m_velocity;
}

void Worker::kinematicWander(sf::Vector2f targetPosition)
{
	//move towards a target with randomized x and y
	m_velocity = targetPosition - m_position;
	m_velocity = normalize(m_velocity);
	float orientation = getNewOrientation(m_sprite.getRotation(), length(m_velocity));
	orientation = orientation + m_maxRotation * ((rand() % 2) - 1);
	m_sprite.setRotation(orientation);
	m_velocity = sf::Vector2f(-sin(orientation), cos(orientation)) * m_maxSpeed;

}

sf::Vector2f Worker::asVector(float orientation)
{
	return sf::Vector2f(sinf(orientation), cosf(orientation));

}

void Worker::render(sf::RenderWindow & window)
{
	//only render if not collected
	if (collected == false) {
		window.draw(m_sprite);
	}
	
}

void Worker::setCollected()
{
	//on collsion with player or sweeper = collected
	collected = true;

}
bool Worker::getCollected()
{
	//check if worker has been collected
	return collected;

}


float Worker::length(sf::Vector2f vel)
{
	//legnth formula
	return (sqrt((vel.x * vel.x) + (vel.y * vel.y)));
}

sf::Vector2f Worker::normalize(sf::Vector2f vel)
{
	//how to normalize a vector
	if (length(vel) != 0)
		return sf::Vector2f(vel.x / length(vel), vel.y / length(vel));
	else
		return vel;
}