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

void Alien_Nest::boundary(float x, float y)
{
	if (x > 2100)
	{
		m_position.x = -100;
	}
	if (x < -100)
	{
		m_position.x = 2100;
	}
	if (y < -100)
	{
		m_position.y = 2100;
	}
	if (y > 2100)
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

void Alien_Nest::kinematicSeek(sf::Vector2f playerPosition)
{
	m_velocity = playerPosition - m_position;
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
void Alien_Nest::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;
			m_velocity = m_velocity * m_maxSpeed;

		}

		m_orientation = getNewOrientation(m_orientation, m_velocityF);
		m_orientation = m_orientation + 180;
	}

}


void Alien_Nest::collison(std::vector<Enemy*> enemies)
{
	for (int i = 0; i < enemies.size(); i++)
	{
		n_direction = enemies[i]->getPosition() - m_position;
		n_distance = std::sqrt(n_direction.x*n_direction.x + n_direction.y* n_direction.y);

		if (n_distance <= radius)
		{
			float dot = (m_velocity.x * n_direction.x) + (m_velocity.y * n_direction.y);
			float det = (m_velocity.x * n_direction.y) - (m_velocity.y * n_direction.x);

			float angle = atan2(det, dot);
			angle = (180 / 3.14) * angle;


			if (angle >= -m_threshold && angle <= m_threshold)
			{
				crash = true;
				m_velocity = -m_velocity;
				m_orientation = -m_orientation;
				//std::cout << "Collided Arrive" << std::endl;

			}

		}
		if (crash == true && n_distance > radius)
		{
			crash = false;
		}
	}
}


sf::Vector2f Alien_Nest::getPosition()
{
	return m_sprite.getPosition();
}
sf::Vector2f Alien_Nest::getVelocity()
{
	return m_velocity;
}


void Alien_Nest::update(sf::Vector2f playerPosition, Player* player, std::vector<Enemy*> enemies)
{
	//collison(enemies);
	if (crash == false)
	{
		kinematicArrive(playerPosition);
	}

	m_position = m_position + m_velocity;

	m_sprite.setPosition(m_position);
	m_sprite.setRotation(m_orientation);

	boundary(m_sprite.getPosition().x, m_sprite.getPosition().y);
}


void Alien_Nest::render(sf::RenderWindow & window)
{
	window.draw(m_sprite);
}