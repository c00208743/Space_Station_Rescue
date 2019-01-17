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
	target = sf::Vector2f(rand() % 6000, rand() % 6000);
}

sf::Vector2f Worker::rotate(sf::Vector2f P, sf::Vector2f O, float theta)
{
	sf::Transform rotTran;
	rotTran.rotate(theta, O.x, O.y);
	return rotTran.transformPoint(P);
}

void Worker::update(Level * cLevel)
{
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
	float posX = m_position.x + 32;
	float posY = m_position.y;
	
	sf::Vector2f tileAhead = rotate(sf::Vector2f(posX, posY), m_sprite.getPosition(), m_sprite.getRotation());

	int x = floor(tileAhead.x / 32);
	int y = floor(tileAhead.y / 32);

	if (cLevel->collide(sf::Vector2i(x, y)))
	{
		newTarget();
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
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;
}

sf::Vector2f Worker::getPosition()
{
	return m_sprite.getPosition();
}
void Worker::setPosition(float x, float y)
{
	
	m_position.x = x;
	m_position.y = y;
}

sf::Vector2f Worker::getVelocity()
{
	return m_velocity;
}

void Worker::kinematicWander(sf::Vector2f targetPosition)
{
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
	if (collected == false) {
		window.draw(m_sprite);
	}
	
}

void Worker::setCollected()
{
	collected = true;

}
bool Worker::getCollected()
{
	return collected;

}


float Worker::length(sf::Vector2f vel)
{
	return (sqrt((vel.x * vel.x) + (vel.y * vel.y)));
}

sf::Vector2f Worker::normalize(sf::Vector2f vel)
{
	if (length(vel) != 0)
		return sf::Vector2f(vel.x / length(vel), vel.y / length(vel));
	else
		return vel;
}