#include "Worker.h"
#include "Player.h"
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
	m_sprite.setOrigin(128, 128);
}


Worker::~Worker()
{
}



void Worker::update(sf::Vector2f playerPosition, Player* player)
{
	kinematicWander(playerPosition);
	//repulseSteering(enemies);
	m_position = m_position + m_velocity;
	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);
	
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

sf::Vector2f Worker::getVelocity()
{
	return m_velocity;
}

void Worker::kinematicWander(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;

	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y*m_velocity.y);

	//Normalize vector
	m_velocity.x = m_velocity.x / m_velocityF;
	m_velocity.y = m_velocity.y / m_velocityF;

	//get new orientation
	m_orientation = getNewOrientation(m_orientation, m_velocityF);

	//orientation = orientation + MaxRotation * random(-1, +1)
	m_orientation = m_orientation + maxRotation * getRandom(-1, 1);

	//Velocity = (-sin(orientation), cos(orientation))*maxSpeed
	m_velocity.x = (-sin(m_orientation))*m_maxSpeed;
	m_velocity.y = cos(m_orientation) *m_maxSpeed;

}


void Worker::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}
