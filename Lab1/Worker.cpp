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
	m_sprite.setOrigin(16, 32);
	/* initialize random seed: */
	srand(time(NULL));
	//m_position.x = rand() % 400 + 1;
	//m_position.y = rand() % 400 + 1;
}


Worker::~Worker()
{
}



void Worker::update(sf::Vector2f playerPosition, Player* player)
{
	if (collected == false) {
		kinematicWander(playerPosition);

		m_position = m_position + m_velocity;
		m_sprite.setPosition(m_position);
		m_sprite.setRotation(m_orientation);
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

void Worker::kinematicWander(sf::Vector2f playerPosition)
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



